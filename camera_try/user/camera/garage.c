/*
 * garage.c
 *
 *  Created on: 2024��10��12��
 *      Author: A
 */

#include "math.h"
#include "headfile.h"
#define M_PI  3.14159265358979323846   // pi

enum garage_type_e garage_type = GARAGE_NONE;

float (*garage_rpts)[2];
int garage_rpts_num;

float calculate_vector_angle(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float vector_length = Q_sqrt(dx * dx + dy * dy);
    float angle_radians = acos(dx / vector_length);
    float angle_degrees = angle_radians * 180 / M_PI;

    return angle_degrees;
}

void CheckGarage()
{
    //������־λ
    int banmaxian_hangshu = 0;//����������

    //��������ɨ��
        for (int y = BEGINH_L + 10; y >= BEGINH_L - 10; y--)
        {
            int banmaxian_kuandu=0;
            //int banmaxian_hangshu=0;
            int banmaxian_geshu=0;
             //��������ɨ��
            for (int x =130; x >=20; x--)
            {
                int baidian_heng=0;
                //ɨ�赽��ɫ���ͽ��ж�
                if (GET_PIX_1C(mt9v03x_image_copy[0], y, x + 2) > FIX_BINTHRESHOLD && GET_PIX_1C(mt9v03x_image_copy[0], y, x + 1) > FIX_BINTHRESHOLD
                && GET_PIX_1C(mt9v03x_image_copy[0], y, x) < FIX_BINTHRESHOLD && GET_PIX_1C(mt9v03x_image_copy[0], y, x - 1) < FIX_BINTHRESHOLD)
                {
                    for (int a = x; a > x - 30; a--)//�Ӻ�ɫ�������ɨ��
                    {
                        //�ҵ���ɫ��
                        if(GET_PIX_1C(mt9v03x_image_copy[0], y, a) > FIX_BINTHRESHOLD && GET_PIX_1C(mt9v03x_image_copy[0], y, a - 1) > FIX_BINTHRESHOLD)
                        {
                            //��¼��ɫ���λ�ã�����ѭ��
                            baidian_heng=a;
                            break;
                        }
                    }//�����߿�ȵ��ںڰ׵�Ĳ�
                    banmaxian_kuandu=x-baidian_heng;


                }
                else
                {   //�����ߵĿ����4~8֮����Ϊ������Ϊ�����ߺ�ɫ��
                    if (banmaxian_kuandu >= 2 && banmaxian_kuandu <= 6)
                    {
                        //�����ߺ�ɫ��++
                        banmaxian_geshu++;
                        //������ɫ�������㣬������һ����ɫ���ɨ�����
                        banmaxian_kuandu = 0;
                    }
                    else
                    {
                        //���������Ժ�ɫ�����ΪҪ���ֱ�����㣬ȥ������һ����ɫ��
                        banmaxian_kuandu = 0;
                    }
                }
            }
            //���ɫ��ĸ�����6~9֮������Ϊ��һ�еİ���������Ҫ����ȥɨ��һ��
            if (banmaxian_geshu >= 6 ){banmaxian_hangshu++;}
        }
        //����д��ڵ���4�е���Ч������
        if(banmaxian_hangshu>=2)
        {
            //�����߱�׼λ��1
            garage_type = GARAGE_FOUND;
        }
        else{garage_type = GARAGE_NONE;}
}

void RunGarage()
{
    if (garage_type == GARAGE_FOUND) {
        printf("ʶ�𵽳���\r\n");
        //garage_type = GARAGE_NONE; // TFIXME ԭ���� garage_type == GARAGE_NONE��ȷ�ϸ��ĺ�������
    }
}
