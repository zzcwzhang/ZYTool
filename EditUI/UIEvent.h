#ifndef UIEVENT_H_
#define UIEVENT_H_
void initialize(int formId);
extern std::string dialogTxt;
void showCommonDialog(std::string str);

extern std::string propDialogTxt;
extern Node *propCtrl;
void showPropDialog(Node* node,std::string str);

//////////////////////////////////////////////////////////////////////////
//单人捕鱼场
void buyuchang_initialize(Node* node);
void buyuchang_register(Node* node);
//control3
void buyuchang_control3_Click(Node *node,Touch* ptouch, Event* event);
//control4
void buyuchang_control4_Click(Node *node,Touch* ptouch, Event* event);
//control11
void buyuchang_control11_Click(Node *node,Touch* ptouch, Event* event);
//control13
void buyuchang_control13_Click(Node *node,Touch* ptouch, Event* event);
//control14
void buyuchang_control14_Click(Node *node,Touch* ptouch, Event* event);
//control15
void buyuchang_control15_Click(Node *node,Touch* ptouch, Event* event);
//control16
void buyuchang_control16_Click(Node *node,Touch* ptouch, Event* event);
//control17
void buyuchang_control17_Click(Node *node,Touch* ptouch, Event* event);
//control21
void buyuchang_control21_Click(Node *node,Touch* ptouch, Event* event);
//control28
void buyuchang_control28_Click(Node *node,Touch* ptouch, Event* event);
//control29
void buyuchang_control29_Click(Node *node,Touch* ptouch, Event* event);
//control30
void buyuchang_control30_Click(Node *node,Touch* ptouch, Event* event);
//control31
void buyuchang_control31_Click(Node *node,Touch* ptouch, Event* event);
//control32
void buyuchang_control32_Click(Node *node,Touch* ptouch, Event* event);
//control33
void buyuchang_control33_Click(Node *node,Touch* ptouch, Event* event);
//control34
void buyuchang_control34_Click(Node *node,Touch* ptouch, Event* event);
//control35
void buyuchang_control35_Click(Node *node,Touch* ptouch, Event* event);
//control36
void buyuchang_control36_Click(Node *node,Touch* ptouch, Event* event);
//control41
void buyuchang_control41_Click(Node *node,Touch* ptouch, Event* event);
void buyuchang_control43_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//多人捕鱼场
void duorenbuyuchang_initialize(Node* node);
void duorenbuyuchang_register(Node* node);
//control7
void duorenbuyuchang_control7_Click(Node *node,Touch* ptouch, Event* event);
//control8
void duorenbuyuchang_control8_Click(Node *node,Touch* ptouch, Event* event);
//control9
void duorenbuyuchang_control9_Click(Node *node,Touch* ptouch, Event* event);
//control10
void duorenbuyuchang_control10_Click(Node *node,Touch* ptouch, Event* event);
//control12
void duorenbuyuchang_control12_Click(Node *node,Touch* ptouch, Event* event);
//control16
void duorenbuyuchang_control16_Click(Node *node,Touch* ptouch, Event* event);
//control17
void duorenbuyuchang_control17_Click(Node *node,Touch* ptouch, Event* event);
//control26
void duorenbuyuchang_control26_Click(Node *node,Touch* ptouch, Event* event);
//control42
void duorenbuyuchang_control42_Click(Node *node,Touch* ptouch, Event* event);
//control43
void duorenbuyuchang_control43_Click(Node *node,Touch* ptouch, Event* event);
//control44
void duorenbuyuchang_control44_Click(Node *node,Touch* ptouch, Event* event);
//control50
void duorenbuyuchang_control50_Click(Node *node,Touch* ptouch, Event* event);
//control51
void duorenbuyuchang_control51_Click(Node *node,Touch* ptouch, Event* event);
//control55
void duorenbuyuchang_control55_Click(Node *node,Touch* ptouch, Event* event);
//control60
void duorenbuyuchang_control60_Click(Node *node,Touch* ptouch, Event* event);
//control61
void duorenbuyuchang_control61_Click(Node *node,Touch* ptouch, Event* event);
//control62
void duorenbuyuchang_control62_Click(Node *node,Touch* ptouch, Event* event);
//control65
void duorenbuyuchang_control65_Click(Node *node,Touch* ptouch, Event* event);
//control66
void duorenbuyuchang_control66_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//单人模式选关
void danrenmoshixuanguan_initialize(Node* node);
void danrenmoshixuanguan_register(Node* node);
//control1
void danrenmoshixuanguan_control1_Click(Node *node,Touch* ptouch, Event* event);
//control2
bool danrenmoshixuanguan_control2_TouchMove(Node *node,Touch* ptouch, Event* event);
//control3
void danrenmoshixuanguan_control3_Click(Node *node,Touch* ptouch, Event* event);
//control7
void danrenmoshixuanguan_control7_Click(Node *node,Touch* ptouch, Event* event);
//control8
void danrenmoshixuanguan_control8_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//任务弹框
void renwutankuang_initialize(Node* node);
void renwutankuang_register(Node* node);
//control5
void renwutankuang_control5_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//更换炮台
void genghuanpaotai_initialize(Node* node);
void genghuanpaotai_register(Node* node);
//control1
//control3
bool genghuanpaotai_control3_TouchMove(Node *node,Touch* ptouch, Event* event);
//control4
void genghuanpaotai_control4_Click(Node *node,Touch* ptouch, Event* event);
//control7
void genghuanpaotai_control7_Click(Node *node,Touch* ptouch, Event* event);
//control10
void genghuanpaotai_control10_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//道具说明
void daojushuoming_initialize(Node* node);
void daojushuoming_register(Node* node);
//control3
void daojushuoming_control3_Click(Node *node,Touch* ptouch, Event* event);
//control4
void daojushuoming_control4_Click(Node *node,Touch* ptouch, Event* event);
//control5
void daojushuoming_control5_Click(Node *node,Touch* ptouch, Event* event);
//control12
void daojushuoming_control12_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//倍率介绍
void beilvjieshao_initialize(Node* node);
void beilvjieshao_register(Node* node);
//control1
//control3
void beilvjieshao_control3_Click(Node *node,Touch* ptouch, Event* event);
//control4
bool beilvjieshao_control4_TouchMove(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//在线奖励
void zaixianjiangli_initialize(Node* node);
void zaixianjiangli_register(Node* node);
//control3
void zaixianjiangli_control3_Click(Node *node,Touch* ptouch, Event* event);
//control11
void zaixianjiangli_control11_Click(Node *node,Touch* ptouch, Event* event);
//control17
void zaixianjiangli_control17_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//多人模式选关
void duorenmoshixuanguan_initialize(Node* node);
void duorenmoshixuanguan_register(Node* node);
//control2
void duorenmoshixuanguan_control2_Click(Node *node,Touch* ptouch, Event* event);
//control4
void duorenmoshixuanguan_control4_Click(Node *node,Touch* ptouch, Event* event);
//control5
void duorenmoshixuanguan_control5_Click(Node *node,Touch* ptouch, Event* event);
//control15
void duorenmoshixuanguan_control15_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//VIP提示弹框
void VIPtishitankuang_initialize(Node* node);
void VIPtishitankuang_register(Node* node);
//control3
void VIPtishitankuang_control3_Click(Node *node,Touch* ptouch, Event* event);
//control4
void VIPtishitankuang_control4_Click(Node *node,Touch* ptouch, Event* event);
//control6
void VIPtishitankuang_control6_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//封面
void fengmian_initialize(Node* node);
void fengmian_register(Node* node);
//control3
void fengmian_control3_Click(Node *node,Touch* ptouch, Event* event);
//control4
void fengmian_control4_Click(Node *node,Touch* ptouch, Event* event);
//control5
void fengmian_control5_Click(Node *node,Touch* ptouch, Event* event);
//control6
void fengmian_control6_Click(Node *node,Touch* ptouch, Event* event);
//control7
void fengmian_control7_Click(Node *node,Touch* ptouch, Event* event);
//control11
void fengmian_control11_Click(Node *node,Touch* ptouch, Event* event);
//control17
void fengmian_control17_Click(Node *node,Touch* ptouch, Event* event);
//control18
void fengmian_control18_Click(Node *node,Touch* ptouch, Event* event);
//control19
void fengmian_control19_Click(Node *node,Touch* ptouch, Event* event);
//control20
void fengmian_control20_Click(Node *node,Touch* ptouch, Event* event);
//control21
void fengmian_control21_Click(Node *node,Touch* ptouch, Event* event);
//control22
void fengmian_control22_Click(Node *node,Touch* ptouch, Event* event);
//control23
void fengmian_control23_Click(Node *node,Touch* ptouch, Event* event);
//control24
void fengmian_control24_Click(Node *node,Touch* ptouch, Event* event);
//control26
void fengmian_control26_Click(Node *node,Touch* ptouch, Event* event);
//control27
void fengmian_control27_Click(Node *node,Touch* ptouch, Event* event);
//control28
void fengmian_control28_Click(Node *node,Touch* ptouch, Event* event);
//control29
void fengmian_control29_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//每日签到
void meiriqiandao_initialize(Node* node);
void meiriqiandao_register(Node* node);
//control24
void meiriqiandao_control24_Click(Node *node,Touch* ptouch, Event* event);
//control25
void meiriqiandao_control25_Click(Node *node,Touch* ptouch, Event* event);
//control33
void meiriqiandao_control33_Click(Node *node,Touch* ptouch, Event* event);
//control37
void meiriqiandao_control37_Click(Node *node,Touch* ptouch, Event* event);
//control45
void meiriqiandao_control45_Click(Node *node,Touch* ptouch, Event* event);
//排行榜
void paihangbang_initialize(Node* node);
void paihangbang_register(Node* node);
//control3
void paihangbang_control3_Click(Node *node,Touch* ptouch, Event* event);
//control4
void paihangbang_control4_Click(Node *node,Touch* ptouch, Event* event);
//control5
void paihangbang_control5_Click(Node *node,Touch* ptouch, Event* event);
//control6
void paihangbang_control6_Click(Node *node,Touch* ptouch, Event* event);
//control7
void paihangbang_control7_Click(Node *node,Touch* ptouch, Event* event);
//control34
void paihangbang_control34_Click(Node *node,Touch* ptouch, Event* event);
//control35
void paihangbang_control35_Click(Node *node,Touch* ptouch, Event* event);
//control26
void paihangbang_control26_Click(Node *node,Touch* ptouch, Event* event);

//control46
void paihangbang_control46_Click(Node *node,Touch* ptouch, Event* event);

//control36
void paihangbang_control36_Click(Node *node,Touch* ptouch, Event* event);
//control37
void paihangbang_control37_Click(Node *node,Touch* ptouch, Event* event);
//control38
void paihangbang_control38_Click(Node *node,Touch* ptouch, Event* event);
//control39
void paihangbang_control39_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//个人信息
void gerenxinxi_initialize(Node* node);
void gerenxinxi_register(Node* node);
//control3
void gerenxinxi_control3_Click(Node *node,Touch* ptouch, Event* event);
//control4
void gerenxinxi_control4_Click(Node *node,Touch* ptouch, Event* event);
//control5
void gerenxinxi_control5_Click(Node *node,Touch* ptouch, Event* event);
//control6
void gerenxinxi_control6_Click(Node *node,Touch* ptouch, Event* event);
//control7
void gerenxinxi_control7_Click(Node *node,Touch* ptouch, Event* event);
//control13
void gerenxinxi_control13_Click(Node *node,Touch* ptouch, Event* event);
//control14
void gerenxinxi_control14_Click(Node *node,Touch* ptouch, Event* event);
//control15
void gerenxinxi_control15_Click(Node *node,Touch* ptouch, Event* event);
//control16
void gerenxinxi_control16_Click(Node *node,Touch* ptouch, Event* event);
//control17
void gerenxinxi_control17_Click(Node *node,Touch* ptouch, Event* event);
//control18
void gerenxinxi_control18_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//登陆窗口
void dengluchuangkou_initialize(Node* node);
void dengluchuangkou_register(Node* node);
//control3
void dengluchuangkou_control3_Click(Node *node,Touch* ptouch, Event* event);
//control4
void dengluchuangkou_control4_Click(Node *node,Touch* ptouch, Event* event);
//control7
void dengluchuangkou_control7_Click(Node *node,Touch* ptouch, Event* event);
//control11
void dengluchuangkou_control11_Click(Node *node,Touch* ptouch, Event* event);
//control13
void dengluchuangkou_control13_Click(Node *node,Touch* ptouch, Event* event);
//control14
void dengluchuangkou_control14_Click(Node *node,Touch* ptouch, Event* event);
//control8
void dengluchuangkou_control8_Click(Node *node,Touch* ptouch, Event* event);
//control9
void dengluchuangkou_control9_Click(Node *node,Touch* ptouch, Event* event);
//control20
void dengluchuangkou_control20_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//金币商城
void jingbishangcheng_initialize(Node* node);
void jingbishangcheng_register(Node* node);
//control1
//control2
bool jingbishangcheng_control2_TouchMove(Node *node,Touch* ptouch, Event* event);
//control3
void jingbishangcheng_control3_Click(Node *node,Touch* ptouch, Event* event);
//control4
void jingbishangcheng_control4_Click(Node *node,Touch* ptouch, Event* event);
//control6
void jingbishangcheng_control6_Click(Node *node,Touch* ptouch, Event* event);
//control10
void jingbishangcheng_control10_Click(Node *node,Touch* ptouch, Event* event);
//control13
void jingbishangcheng_control13_Click(Node *node,Touch* ptouch, Event* event);
//control14
void jingbishangcheng_control14_Click(Node *node,Touch* ptouch, Event* event);
//control25
void jingbishangcheng_control25_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//过关
void gameend_initialize(Node* node);
void gameend_register(Node* node);
//control1
//control4
void gameend_control4_Click(Node *node,Touch* ptouch, Event* event);
//control5
void gameend_control5_Click(Node *node,Touch* ptouch, Event* event);
//control6
void gameend_control6_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//解锁炮弹
void jiesuopaodan_initialize(Node* node);
void jiesuopaodan_register(Node* node);
//control3
bool jiesuopaodan_control3_TouchMove(Node *node,Touch* ptouch, Event* event);
//control4
void jiesuopaodan_control4_Click(Node *node,Touch* ptouch, Event* event);
//control12
void jiesuopaodan_control12_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//残忍退出
void canrentuichu_initialize(Node* node);
void canrentuichu_register(Node* node);
//control1
//control2
void canrentuichu_control2_Click(Node *node,Touch* ptouch, Event* event);
//control3
void canrentuichu_control3_Click(Node *node,Touch* ptouch, Event* event);
//control4
void canrentuichu_control4_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//获得火炮
void huodehuopao_initialize(Node* node);
void huodehuopao_register(Node* node);
//control3
void huodehuopao_control3_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//邮箱
void email_initialize(Node* node);
void email_register(Node* node);
//control1
//control3
void email_control3_Click(Node *node,Touch* ptouch, Event* event);
//control4
void email_control4_Click(Node *node,Touch* ptouch, Event* event);
//control5
void email_control5_Click(Node *node,Touch* ptouch, Event* event);
//control6
//control18
//control19
//control20
//control21
void email_control21_Click(Node *node,Touch* ptouch, Event* event);
void email_control8_Click(Node *node,Touch* ptouch, Event* event);
void email_control18_Click(Node *node,Touch* ptouch, Event* event);
void email_control19_Click(Node *node,Touch* ptouch, Event* event);
void email_control7_Paint(Node *node);
void email_update(Node *node,float dt);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//礼品商城
void lipingshangcheng_register(Node* node);
void lipingshangcheng_initialize(Node* node);
//control5
void lipingshangcheng_control5_Click(Node *node,Touch* ptouch, Event* event);
//control8
void lipingshangcheng_control8_Click(Node *node,Touch* ptouch, Event* event);
//control9
void lipingshangcheng_control9_Click(Node *node,Touch* ptouch, Event* event);
//control10
void lipingshangcheng_control10_Click(Node *node,Touch* ptouch, Event* event);
//control11
void lipingshangcheng_control11_Click(Node *node,Touch* ptouch, Event* event);
//control14
void lipingshangcheng_control14_Click(Node *node,Touch* ptouch, Event* event);
//control19
void lipingshangcheng_control19_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//要2块钱
void yao2yuan_register(Node* node);
void yao2yuan_initialize(Node* node);
//control3
void yao2yuan_control3_Click(Node *node,Touch* ptouch, Event* event);
//control4
void yao2yuan_control4_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//道具提示框
void daojutishikuang_register(Node* node);
void daojutishikuang_initialize(Node* node);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//通用提示
void tongyongtishi_register(Node* node);
void tongyongtishi_initialize(Node* node);
//control2
//control4
void tongyongtishi_control4_Click(Node *node,Touch* ptouch, Event* event);
//////////////////////////////////////////////////////////////////////////
#endif
