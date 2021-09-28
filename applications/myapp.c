#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <drv_dcmi.h>

// #include "drv_ov2640.h"

#define BUFF_SIZE 1024
extern rt_uint32_t *jpeg_data_buf;
extern volatile rt_uint8_t  jpeg_data_ok;
extern volatile rt_uint32_t jpeg_data_len;

static rt_uint8_t *p = RT_NULL;
static rt_uint32_t jpg_len = 0;

static const char *send_data = "hello RT-Thread\n";


void prepare_jpeg(){
    rt_uint8_t jpg_head = 0;
    rt_uint32_t i, jpg_start;
    DCMI_Start();

    while (jpeg_data_ok != 1);
    jpeg_data_ok = 2;
    while (jpeg_data_ok != 1);
    DCMI_Stop();

    p = (rt_uint8_t *)jpeg_data_buf;
    jpg_len  = 0;
    jpg_head = 0;
    for (i = 0; i < jpeg_data_len * 4; i++)
   {
        /* jpg head */
        if ((p[i] == 0xFF) && (p[i + 1] == 0xD8))
        {
           jpg_start = i;
           jpg_head = 1;
        }
        /* jpg end */
        if ((p[i] == 0xFF) && (p[i + 1] == 0xD9) && jpg_head)
        {
           jpg_len = i - jpg_start + 2; /* a picture len */
           break;
        }
   }
    if (jpg_len){
        p += jpg_start;
    }else{
        p = RT_NULL;
    }
}

void tcpserver(int argc, char **argv)
{
    int sock_listen, sock_connect, port;
    struct hostent *host;
    struct sockaddr_in listen_addr;
    struct sockaddr_in connect_addr;
    const char *url;

    url = "192.168.3.57";   //localhost ip
    port = 5000;
    /* ͨ��������ڲ��� url ��� host ��ַ��������������������������� */
    host = (struct hostent *) gethostbyname(url);

    /* ����һ�� socket�������� SOCK_DGRAM��UDP ���� */
    /*SOCK_STREAM => TCP*/
    if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        rt_kprintf("Socket error\n");
        return;
    }

    /* ��ʼ��Ԥ���ӵķ���˵�ַ */
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

            prepare_jpeg();
            if( p != RT_NULL){
                send(sock_connect, &jpg_len, sizeof(jpg_len), 0);
                rt_thread_delay(5);

                /* �������ݵ�����Զ�� */
                // send(sock_connect, send_data, strlen(send_data), 0);
                int offset = 0;
                while(1){
                    if(offset + BUFF_SIZE < jpg_len){
                        send(sock_connect, p+offset, BUFF_SIZE, 0);
                        offset += BUFF_SIZE;
                        rt_thread_delay(5);
                    }else{
                        send(sock_connect, p+offset, jpg_len - offset, 0);
                        break;
                    }
                }
            }
        }
        closesocket(sock_connect);

    }

    __exit:
    /* �ر���� socket */
    closesocket(sock_listen);
}
MSH_CMD_EXPORT(tcpserver, tcpserver);
