create table HK		                            /*������Ϣ��*/
( Hno char(20) primary key not null,	/*����*/
Hname char(20) not null,              	/*��������*/
ID char(20) not null,							/*���֤��*/
Nation char(20) not null,					/*����*/
Ads varchar(20) not null,					/*סַ*/
Indate Datetime not null,					/*Ǩ��ʱ��*/
wherein varchar(20) not null,				/*�ε�Ǩ��*/
Outdata Datetime,							/*Ǩ������*/
Whereout varchar(20));						/*Ǩ���ε�*/

create table RK									/*�˿���Ϣ��*/
( Rname char(20) not null,
Rsex char(2) not null,
ID char(20) primary key not null,
Nation char(20) not null,
Province char(20) not null,
Birdate Datetime not null,
Birpace varchar(20),
Ads varchar(20));

create table GL									/*����Ա��Ϣ��*/
( Gname char(20) not null,
Number char(20) primary key not null,
Sex char(2),
Paswd varchar(20) not null);

create table RIN								/*�˿�Ǩ����Ϣ��*/
( Hno char(20) not null,
Relation char(20) not null,
ID char(20) not null,
Indate Datetime not null,
wherein varchar(20) not null,
bollout char(20) not null,
foreign key (Hno) references HK(Hno),
foreign key(ID) references RK(ID));

