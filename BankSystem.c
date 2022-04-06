#include <stdio.h>
#include <string.h>
#include <windows.h>
#define NUM 100
FILE *fp;
FILE *fpp;
struct log
{
    int num;
    int card_num;
    char type[20];
    double money_change;
    double money;
};
struct customer
{
    int card_num;
    int card_pswd;
    char name[20];
    double id_num;
    double phone_num;
    char address[50];
    double money;
    int sign;
};
struct log logg[NUM] = {
    {1, 10001, "开户", 1000, 1000},
    {0, 10002, "开户", 100, 100}};
struct customer cus[NUM] = {
    {10001, 123123, "徐健钧", 370683200306299311, 12345678, "北京紫荆城", 1000, 1},
    {10002, 321321, "刘铭", 370683200306299312, 321321321, "北京大学", 100, 1}};

int main_menu(void);
int customer_system_log_in(void);
int customer_menu(void);
int admin_system_log_in(void);
int admin_menu(void);
int addcus(void);
int find();
int findall();
int account_log();
int save(void);
int load(void);
main()
{
    system("mode con cols=200 lines=30");
    if ((fopen("date.dat", "r") == NULL) || (fopen("log.dat", "r") == NULL))
    {
        save();
    }
    else
        load();
    for (;;)
    {
        save();
        main_menu();
        system("cls");
    }
    return 0;
}
int main_menu(void)
{
    int choice_num;
    printf("欢迎使用银行管理系统\n\n\n用户账号1：10001，123123 \n用户账号2：10002，321321 \n管理员账号密码：admin，admin\n\n\n请选择登陆身份：\n1：用户\n\n2：管理员\n\n请输入：");
    scanf("%d", &choice_num);
    if (choice_num == 1)
    { //用户系统
        printf("请登录（用户）\n");
        customer_system_log_in();
    }
    else
    { // 管理员系统
        printf("请登录（管理员）\n");
        admin_system_log_in();
    }
    return 0;
}
int customer_system_log_in(void)
{
    int input_card_num, input_card_pswd, sign = 0, i;

    printf("请输入卡号：");
    scanf("%d", &input_card_num);
    for (i = 0; i <= NUM; i++)
    {

        if (cus[i].card_num == input_card_num)
        {
            sign = 1;
            break;
        }
    }
    if (sign == 0 || cus[i].sign == 0)
    {
        printf("未找到该卡号:%d，请重试\n", input_card_num);
        system("pause");
    }
    else
    {
        printf("请输入密码：");
        scanf("%d", &input_card_pswd);
        if (cus[i].card_pswd == input_card_pswd)
        {
            printf("登陆成功\n");
            //进入用户主菜单
            for (;;)
                customer_menu(i);
        }
        else
        {
            printf("密码错误，请重新登录\n");
            system("pause");
            main_menu();
        }
    }
    return 0;
}
int customer_menu(int i)
{
    int input_num, sign = 0, j;
    double money;
    printf("请输入要办理的业务的编号：\n");
    printf("1.查询余额\n");
    printf("2.存款\n");
    printf("3.取款\n");
    printf("4.转账\n");
    printf("5.查询明细\n");
    printf("6.交易记录\n");
    printf("7.退卡\n");
    scanf("%d", &input_num);
    switch (input_num)
    {
    case 1:
        printf("您的账号：%d\n可用余额为%lf\n", cus[i].card_num, cus[i].money);
        break;
    case 2:
        printf("请输入存款金额：");
        scanf("%lf", &money);
        cus[i].money += money;
        printf("成功存入%lf元，现有余额%lf元\n", money, cus[i].money);
        logg[logg[0].num].card_num = cus[i].card_num;
        strcpy(logg[logg[0].num].type, "存款");
        logg[logg[0].num].money_change = money;
        logg[logg[0].num].money = cus[i].money;
        logg[0].num++;
        break;
    case 3:
        printf("请输入取款金额：");
        scanf("%lf", &money);
        cus[i].money -= money;
        printf("成功取出%lf元，现有余额%lf元\n", money, cus[i].money);
        logg[logg[0].num].card_num = cus[i].card_num;
        strcpy(logg[logg[0].num].type, "取款");
        logg[logg[0].num].money_change = -money;
        logg[logg[0].num].money = cus[i].money;
        logg[0].num++;
        break;
    case 4:
        printf("请输入转账账户：");
        scanf("%d", &input_num);
        printf("请输入转账金额：");
        scanf("%lf", &money);
        for (j = 0; j <= NUM; j++)
        {

            if (cus[j].card_num == input_num)
            {
                sign = 1;
                break;
            }
        }
        if (sign == 0)
        {
            printf("未找到该卡号:%d，请重试\n", input_num);
            system("pause");
        }
        else
        {
            cus[j].money += money;
            cus[i].money -= money;
            printf("成功转账%lf元，现有余额%lf元\n", money, cus[i].money);
            logg[logg[0].num].card_num = cus[i].card_num;
            strcpy(logg[logg[0].num].type, "转账");
            logg[logg[0].num].money_change = -money;
            logg[logg[0].num].money = cus[i].money;
            logg[0].num++;
            logg[logg[0].num].card_num = cus[j].card_num;
            strcpy(logg[logg[0].num].type, "转账");
            logg[logg[0].num].money_change = money;
            logg[logg[0].num].money = cus[i].money;
            logg[0].num++;
            break;
        }
    case 5:
        printf("您的账户明细：姓名          身份证号                     电话号码                      家庭住址                      卡号                        可用余额\n");
        printf("              %-s        %-20.0lf         %-20.0lf          %-20s          %-20d        %-20lf\n", cus[i].name, cus[i].id_num, cus[i].phone_num, cus[i].address, cus[i].card_num, cus[i].money);
        break;
    case 6:
        account_log(i);
        break;
    case 7:
        system("pause");
        save();
        main_menu();
    default:
        break;
    }
    system("pause");
    return 0;
}
int admin_system_log_in(void)
{
    char admin[] = "admin", input_user[20], input_pswd[20];
    printf("请输入管理员账号：");
    scanf("%s", &input_user);
    printf("请输入管理员密码：");
    scanf("%s", &input_pswd);
    if (strcmp(input_user, admin) == 0 && strcmp(input_pswd, admin) == 0)
    {
        printf("登陆成功 ");
        for (;;)
            admin_menu();
    }
    else
    {
        printf("认证失败，请重新登录 \n");
        system("pause");
    }
    return 0;
}
int admin_menu(void)
{
    int input_num, sign = 0, i;
    printf("请输入要进行的操作：\n");
    printf("1.开户\n");
    printf("2.查询指定账户信息\n");
    printf("3.查询所有账户信息\n");
    printf("4.销户\n");
    printf("5.保存&退出\n");
    scanf("%d", &input_num);
    switch (input_num)
    {
    case 1:
        addcus();
        break;
    case 2:
        find();
        break;
    case 3:
        findall();
        break;
    case 4:
        printf("请输入要销户的卡号：");

        scanf("%d", &input_num);
        for (i = 0; i <= NUM; i++)
        {

            if (cus[i].card_num == input_num)
            {
                sign = 1;
                break;
            }
        }
        if (sign == 0 || cus[i].sign == 0)
        {
            printf("未找到该卡号:%d，请重试\n", input_num);
            system("pause");
        }
        else
        {
            cus[i].sign = 0;
            printf("账号%d 销户成功\n", input_num);
            system("pause");
        }
        break;
    case 5:
        system("pause");
        save();
        main_menu();
    default:
        break;
    }
    return 0;
}

int addcus(void)
{

    int i;
    for (i = 0; i < NUM; i++)
    {
        if (cus[i].sign == 0)
        {
            printf("开始创建新用户，请输入姓名，身份证号码，电话号码，家庭住址，银行卡号,密码 以空格分隔\n");
            scanf("%s %lf %lf %s %d %d", &cus[i].name, &cus[i].id_num, &cus[i].phone_num, &cus[i].address, &cus[i].card_num, &cus[i].card_pswd);
            printf("新用户信息\n 姓名     身份证号码     电话号码     家庭住址     银行卡号     密码\n\n");
            printf("%s     %.0lf          %.0lf         %s     %d        %d\n", cus[i].name, cus[i].id_num, cus[i].phone_num, cus[i].address, cus[i].card_num, cus[i].card_pswd);
            cus[i].sign = 1;
            logg[logg[0].num].card_num = cus[i].card_num;
            strcpy(logg[logg[0].num].type, "开户");
            logg[logg[0].num].money_change = 0;
            logg[logg[0].num].money = 0;
            logg[0].num++;
            system("pause");
            break;
        }
    }
    return 0;
}

int find(void)
{
    int input_num, sign = 0, i;
    printf("请输入查询的卡号");
    scanf("%d", &input_num);
    for (i = 0; i <= NUM; i++)
    {

        if (cus[i].card_num == input_num)
        {
            sign = 1;
            break;
        }
    }
    if (sign == 0 || cus[i].sign == 0)
    {
        printf("未找到该卡号:%d，请重试\n", input_num);
        system("pause");
    }
    else
    {
        printf("账户明细：姓名          身份证号                     电话号码                      家庭住址                      卡号                        可用余额\n");
        printf("           %-s        %-20.0lf         %-20.0lf          %-20s          %-20d        %-20lf\n", cus[i].name, cus[i].id_num, cus[i].phone_num, cus[i].address, cus[i].card_num, cus[i].money);
        system("pause");
    }
    return 0;
}
int findall(void)
{
    int input_num, sign = 0, i;
    printf("账户明细：姓名          身份证号                     电话号码                      家庭住址                      卡号                        可用余额\n");
    for (i = 0; i <= NUM; i++)
    {

        if (cus[i].sign == 1)
        {
            printf("           %-s        %-20.0lf         %-20.0lf          %-20s          %-20d        %-20lf\n", cus[i].name, cus[i].id_num, cus[i].phone_num, cus[i].address, cus[i].card_num, cus[i].money);
        }
    }
    system("pause");
    return 0;
}
int account_log(int i)
{
    int j;
    printf("交易记录查询：\n卡号       交易类型      金额变化      余额\n");
    for (j = 0; j <= NUM; j++)
    {
        if (cus[i].card_num == logg[j].card_num)
            printf("%d         %s    %lf      %lf\n", logg[j].card_num, logg[j].type, logg[j].money_change, logg[j].money);
    }
    return 0;
}

int save(void)
{
    fp = fopen("date.dat", "wb");
    fwrite(&cus, sizeof(struct customer), NUM, fp);
    fclose(fp);
    fpp = fopen("log.dat", "wb");
    fwrite(&logg, sizeof(struct log), NUM, fpp);
    fclose(fpp);
    return 0;
}

int load(void)
{
    fp = fopen("date.dat", "rb");
    fread(&cus, sizeof(struct customer), NUM, fp);
    fclose(fp);
    fpp = fopen("log.dat", "rb");
    fread(&logg, sizeof(struct log), NUM, fpp);
    fclose(fpp);
    return 0;
}
