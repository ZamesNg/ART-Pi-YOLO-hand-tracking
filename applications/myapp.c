#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <drv_dcmi.h>
#include <rt_ai.h>
#include <rt_ai_log.h>
#include <rt_ai_network_model.h>
#include <math.h>

#define BUFF_SIZE 256

#define JPEG_LINE_SIZE  (160 * 160)

static rt_uint32_t jpg_len = JPEG_LINE_SIZE;
static rt_uint32_t jpg_len_byte = JPEG_LINE_SIZE*sizeof(float);

static rt_ai_buffer_t work_buffer[RT_AI_NETWORK_WORK_BUFFER_BYTES +
                                  RT_AI_NETWORK_IN_TOTAL_SIZE_BYTES +
                                  RT_AI_NETWORK_OUT_TOTAL_SIZE_BYTES];
rt_ai_t model = RT_AI_NULL;
static float anchor[6][2] = {{13,24}, {33,42}, {36,87}, {94,63}, {68,118}, {132,129}};

float *input_ptr = RT_NULL;
float result[6];

extern struct rt_event ov2640_event;

int ai_run_complete_flag = 0;
void ai_run_complete(void *arg) { *(int *)arg = 1; }

int network_init(void){
    int result = 0;
    model = rt_ai_find(RT_AI_NETWORK_MODEL_NAME);
    if (model == RT_AI_NULL) {
        rt_kprintf("can't find model!\r\n");
        return RT_ERROR;
    }

    result = rt_ai_init(model, work_buffer);
    if (result != 0) {
        rt_kprintf("can't init model!\r\n");
        return RT_ERROR;
    }

    input_ptr = (float *)model->input[0];

    rt_kprintf("init model succ!\r\n");
    return RT_EOK;
}

// INIT_APP_EXPORT(network_init);

int yolo_decode(float *out_data) {
    int j = 0, k = 0, l = 0;
    float max_conf = -1.0f;
    for (int i = 0; i < 5 * 5 * 5; i++) {
        float x_tmp = 1 / (1 + exp(-out_data[i * 6 + 0]));
        float y_tmp = 1 / (1 + exp(-out_data[i * 6 + 1]));
        float box_x = (x_tmp + k) / 5;
        float box_y = (y_tmp + l) / 5;

        float box_w = (exp(out_data[i * 6 + 2]) * anchor[j][0]) / 160.0;
        float box_h = (exp(out_data[i * 6 + 3]) * anchor[j][1]) / 160.0;

        float objectness = 1 / (1 + exp(-out_data[i * 6 + 4]));

        float class_scores = 1 / (1 + exp(-out_data[i * 6 + 5]));

        // char str[100];
        // sprintf(str,"%d %d %d %.3f %.3f, %.3f %.3f, %.3f %.3f\n", j,k,l, box_x, box_y,
        // box_w, box_h, objectness, class_scores);
        // rt_kprintf(str);

        if(objectness > max_conf){
            max_conf = objectness;
            result[0] = box_x;
            result[1] = box_y;
            result[2] = box_w;
            result[3] = box_h;
            result[4] = objectness;
            result[5] = class_scores;
        }

        if (j++ >= 4) {
            j = 0;
            if (k++ >= 4) {
                k = 0;
                if (l++ >= 4) {
                    l = 0;
                }
            }
        }
    }
    return 0;
}

int network_app(void) {
    int result;

    result = rt_ai_run(model, ai_run_complete, &ai_run_complete_flag);

    if (ai_run_complete_flag) {
        float *out = (float *)rt_ai_output(model, 0);
        yolo_decode(out);
    }
    return 0;
}
MSH_CMD_EXPORT(network_app, network demo);


void tcpserver(int argc, char **argv)
{
    int sock_listen, sock_connect, port;
    struct hostent *host;
    struct sockaddr_in listen_addr;
    struct sockaddr_in connect_addr;
    const char *url;

    network_init();

    url = "192.168.137.218";
    port = 5000;

    host = (struct hostent *) gethostbyname(url);

    if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        rt_kprintf("Socket error\n");
        return;
    }

    listen_addr.sin_family = AF_INET;
    listen_addr.sin_port = htons(port);
    listen_addr.sin_addr = *((struct in_addr *) host->h_addr);
    rt_memset(&(listen_addr.sin_zero), 0, sizeof(listen_addr.sin_zero));

    if (bind(sock_listen, (struct sockaddr * )&listen_addr, sizeof(struct sockaddr)) < 0)
    {
        rt_kprintf("Bind fail!\n");
        goto __exit;
    }
    listen(sock_listen, 10);
    int sin_size = sizeof(struct sockaddr_in);

    while(1){

        sock_connect = accept(sock_listen, (struct sockaddr* )&connect_addr, &sin_size);
        rt_kprintf("accpect connection\t%s:%d\n", inet_ntoa(connect_addr.sin_addr), ntohs(connect_addr.sin_port));

        char str[100];
        memset(str, 0, sizeof(str));

        while(1){
            recv(sock_connect, str, sizeof(str), 0);

            rt_kprintf("%s:%d=>%s\n", inet_ntoa(connect_addr.sin_addr), ntohs(connect_addr.sin_port), str);

            if(!(str[0] == 'O' && str[1]=='K'))
                break;

            DCMI_Start();
            rt_event_recv(&ov2640_event,
                            1,
                            RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER,
                            RT_NULL);

            //rt_kprintf("DCMI_Start!\n");
            //DCMI_Start();

            rt_kprintf("network_app!\n");
            network_app();

            rt_kprintf("send!\n");
            send(sock_connect, result, sizeof(result), 0);

            if( input_ptr != RT_NULL){
                rt_kprintf("send2!\n");
                send(sock_connect, &jpg_len_byte, sizeof(jpg_len_byte), 0);

                rt_thread_delay(5);

                int offset = 0;
                while(1){

                    if(offset + BUFF_SIZE < jpg_len){
                        send(sock_connect, input_ptr+offset, BUFF_SIZE*sizeof(float), 0);
                        offset += BUFF_SIZE;
                        rt_thread_delay(5);
                    }else{
                        send(sock_connect, input_ptr+offset, (jpg_len - offset)*sizeof(float), 0);
                        break;
                    }
                }
            }
        }
        closesocket(sock_connect);

    }

    __exit:
    closesocket(sock_listen);
}
MSH_CMD_EXPORT(tcpserver, tcpserver);

