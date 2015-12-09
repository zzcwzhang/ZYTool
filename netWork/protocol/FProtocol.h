#ifndef FPROTOCOL_H
#define	FPROTOCOL_H
/************************************************************************/
/*  服务器ip port                                                                  */
/************************************************************************/

/************************************************************************/
/*  数据上传
** 游戏数据
* 	等级（level）byte
* 	Vip等级（vip）byte
* 	金币（coin）int
* 	充值积分（chargeScore）int
* 	鱼分（fishScore）int
* 	获赞次数（liked）int //这个直接保存在服务器的不用传
* 	在线时长单位为秒（onlineTimes）int
* 	定屏  (propPause)  int
* 	极速（propTopspeed）int //导弹
* 	狂暴（propRage）int
* 	锁定（propLock）int
* 	10000炮（propThousand）int // 能量炮
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
/*  fish模块 协议                                                                    */
/************************************************************************/
enum Module{
	HEART = 1,//心跳模块
	USER = 100,//用户基本操作模块
	RANK = 101,//排行榜模块
	MAIL = 102 //邮件模块
};
/************************************************************************/
/* 用户模块                                                                     */
/************************************************************************/
enum CmdUser{
	 FISH_REGISTER = 100,//注册
	 FISH_LOGIN = 101, //登录
	 FISH_NICKNAME = 102,//上传昵称
	 FISH_RANDOM = 103,//随机昵称
	 FISH_SIGN = 104,//签到
	 FISH_SAVE = 105//上传数据
};

/************************************************************************/
/* 排行榜模块                                                                     */
/************************************************************************/
enum CmdRank{
	 BIGRANK = 1,  //土豪榜
	 SUPERRANK = 2,//捕鱼达人榜
	 TIMERANK = 3,//在线榜
	 LIKEDRANK = 4,//被赞榜

	 BIGRANKSELF = 5,//个人排名  土豪榜
	 SUPERRANKSELF = 6,//个人排名  捕鱼达人榜
	 TIMERANKSELF = 7,//个人排名  在线榜
	 LIKEDRANKSELF = 8,//个人排名  被赞榜

	 TICKETRANK = 9,//奖券达人榜
	 TICKETRANKSELF = 10,//个人排名 奖券达人榜

	 LIKE = 11//点赞
};

/************************************************************************/
/* 邮件模块                                                                     */
/************************************************************************/
enum CmdMail{
	 LOADMAILS = 1,//加载邮件列表(loadMalis)
	 LOADMAIL = 2,//读取邮件(loadMail)
	 DELETEMAIL = 3,//删除单个(deleteMail)
	 DELETEMAILS = 4,//批量删除(deleteMails)
	 ACQUIREATM = 5,//领取附件奖励（acquireAtm）
	 ACQUIREATMS = 6//l领取所有为领取附件奖励(acquireAtms)
};

/************************************************************************/
/* 错误标记                                                                     */
/************************************************************************/
enum ErrorCode{
	 ERRORUNKNOWN = -1,//服务器繁忙 未知错误
	 ERRORUSEREXIST = 0,//用户名已存在
	 ERRORHAVESIGN = 1,//已签到
	 ERRORUSERNOTEXIST = 2,//用户名不存在
	 ERRORPSDERR = 3,//密码错误

	 ERRORSAMENICKNAME = 10,//昵称已存在
	 ERRORRANDOMNICKNAME = 11,//随机昵称失败
	 ERRORSIGNERR = 13, //签到失败
	 ERRORSAVEERR = 34,//上传数据失败

	 ERRORLIKED = 14, //点赞失败
	 ERRORRENK = 15, //获取排行榜失败
	 ERRORRANKSELF = 16,//获取个人排行榜失败
	 ERRORLIKEDFULL = 17,//今日点赞次数已用完
	 ERRORLIKEDEXIST = 18,//此用户已点赞过

	//mail
	 ERRORHAVEATM = 30,//附件已领取
	 ERRORATMALL = 31,//附件已全部领取
	 ERRORLOADMAIL = 32,//加载邮件失败
	 ERRORDELETEMAIL = 33//删除邮件失败
};

/************************************************************************/
/* 签到奖励                                                                     */
/************************************************************************/
enum SignType{

	 FAILED = -1,//签到失败
	 SIGNED = 0,//当天已签过
	 NORMAL = 1,//签到成功无奖励
	 SEQ2 = 2,//连续2天
	 SEQ3 = 3,//连续3天
	 SEQ4 = 4,//连续4天
	 SEQ5 = 5,//连续5天
	 SEQ6 = 6,//连续6天
	 SEQ7 = 7,//连续7天
	 SEQ15 = 15,//签满15天
	 SEQ25 = 25,//签满25天

};

/************************************************************************/
/* 心跳模块                                                                     */
/************************************************************************/
enum CmdHeart{
	//心跳命令
	HEART_HEART = 0
};
#endif	/* BITS_H */