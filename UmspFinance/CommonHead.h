#ifndef _HDSY_COMMONHEAD_H
#define _HDSY_COMMONHEAD_H
//������󳤶ȣ����ӱ���������
#define MSG_MAX_LEN	8196
#define MSG_MAX_CNT	200
#define MAX_SYN_TRS	100
//�Զ�����Ϣ
#define MSG_START_TRANS	(WM_USER+1000)
#define MSG_END_ALL_TRANS (WM_USER+1001)
#define MSG_TRS_THREAD_END (WM_USER+1002)

#include "umspAdap.h"
#include "umspEBAdap.h"
#include "umspErrorCode.h"
#include "umspEBTrans.h"
#include "HDSYC8583Digram.h"
#endif