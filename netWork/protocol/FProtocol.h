#ifndef FPROTOCOL_H
#define	FPROTOCOL_H
/************************************************************************/
/*  ������ip port                                                                  */
/************************************************************************/

/************************************************************************/
/*  �����ϴ�
** ��Ϸ����
* 	�ȼ���level��byte
* 	Vip�ȼ���vip��byte
* 	��ң�coin��int
* 	��ֵ���֣�chargeScore��int
* 	��֣�fishScore��int
* 	���޴�����liked��int //���ֱ�ӱ����ڷ������Ĳ��ô�
* 	����ʱ����λΪ�루onlineTimes��int
* 	����  (propPause)  int
* 	���٣�propTopspeed��int //����
* 	�񱩣�propRage��int
* 	������propLock��int
* 	10000�ڣ�propThousand��int // ������
/************************************************************************/
#define F_level "level"
#define F_vip "vip"
#define F_coin "coin"
#define F_chargeScore "chargeScore"
#define F_fishScore "fishScore"
#define F_onlineTimes "onlineTimes"
#define F_propPause "propPause"
#define F_propTopspeed "propTopspeed"
#define F_propRage "propRage"
#define F_propLock "propLock"
#define F_propThousand "propThousand"

#define FIP "192.168.1.2"
//#define FIP "114.215.181.234"
#define FPORT 9999
/************************************************************************/
/*  fishģ�� Э��                                                                    */
/************************************************************************/
enum Module{
	HEART = 1,//����ģ��
	USER = 100,//�û���������ģ��
	RANK = 101,//���а�ģ��
	MAIL = 102 //�ʼ�ģ��
};
/************************************************************************/
/* �û�ģ��                                                                     */
/************************************************************************/
enum CmdUser{
	 FISH_REGISTER = 100,//ע��
	 FISH_LOGIN = 101, //��¼
	 FISH_NICKNAME = 102,//�ϴ��ǳ�
	 FISH_RANDOM = 103,//����ǳ�
	 FISH_SIGN = 104,//ǩ��
	 FISH_SAVE = 105//�ϴ�����
};

/************************************************************************/
/* ���а�ģ��                                                                     */
/************************************************************************/
enum CmdRank{
	 BIGRANK = 1,  //������
	 SUPERRANK = 2,//������˰�
	 TIMERANK = 3,//���߰�
	 LIKEDRANK = 4,//���ް�

	 BIGRANKSELF = 5,//��������  ������
	 SUPERRANKSELF = 6,//��������  ������˰�
	 TIMERANKSELF = 7,//��������  ���߰�
	 LIKEDRANKSELF = 8,//��������  ���ް�

	 TICKETRANK = 9,//��ȯ���˰�
	 TICKETRANKSELF = 10,//�������� ��ȯ���˰�

	 LIKE = 11//����
};

/************************************************************************/
/* �ʼ�ģ��                                                                     */
/************************************************************************/
enum CmdMail{
	 LOADMAILS = 1,//�����ʼ��б�(loadMalis)
	 LOADMAIL = 2,//��ȡ�ʼ�(loadMail)
	 DELETEMAIL = 3,//ɾ������(deleteMail)
	 DELETEMAILS = 4,//����ɾ��(deleteMails)
	 ACQUIREATM = 5,//��ȡ����������acquireAtm��
	 ACQUIREATMS = 6//l��ȡ����Ϊ��ȡ��������(acquireAtms)
};

/************************************************************************/
/* ������                                                                     */
/************************************************************************/
enum ErrorCode{
	 ERRORUNKNOWN = -1,//��������æ δ֪����
	 ERRORUSEREXIST = 0,//�û����Ѵ���
	 ERRORHAVESIGN = 1,//��ǩ��
	 ERRORUSERNOTEXIST = 2,//�û���������
	 ERRORPSDERR = 3,//�������

	 ERRORSAMENICKNAME = 10,//�ǳ��Ѵ���
	 ERRORRANDOMNICKNAME = 11,//����ǳ�ʧ��
	 ERRORSIGNERR = 13, //ǩ��ʧ��
	 ERRORSAVEERR = 34,//�ϴ�����ʧ��

	 ERRORLIKED = 14, //����ʧ��
	 ERRORRENK = 15, //��ȡ���а�ʧ��
	 ERRORRANKSELF = 16,//��ȡ�������а�ʧ��
	 ERRORLIKEDFULL = 17,//���յ��޴���������
	 ERRORLIKEDEXIST = 18,//���û��ѵ��޹�

	//mail
	 ERRORHAVEATM = 30,//��������ȡ
	 ERRORATMALL = 31,//������ȫ����ȡ
	 ERRORLOADMAIL = 32,//�����ʼ�ʧ��
	 ERRORDELETEMAIL = 33//ɾ���ʼ�ʧ��
};

/************************************************************************/
/* ǩ������                                                                     */
/************************************************************************/
enum SignType{

	 FAILED = -1,//ǩ��ʧ��
	 SIGNED = 0,//������ǩ��
	 NORMAL = 1,//ǩ���ɹ��޽���
	 SEQ2 = 2,//����2��
	 SEQ3 = 3,//����3��
	 SEQ4 = 4,//����4��
	 SEQ5 = 5,//����5��
	 SEQ6 = 6,//����6��
	 SEQ7 = 7,//����7��
	 SEQ15 = 15,//ǩ��15��
	 SEQ25 = 25,//ǩ��25��

};

/************************************************************************/
/* ����ģ��                                                                     */
/************************************************************************/
enum CmdHeart{
	//��������
	HEART_HEART = 0
};
#endif	/* BITS_H */