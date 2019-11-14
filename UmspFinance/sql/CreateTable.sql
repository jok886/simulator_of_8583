/*job_id  smallint
      IDENTITY(1,1)
      PRIMARY KEY CLUSTERED,
   job_desc        varchar(50)     NOT NULL
      DEFAULT 'New Position - title not formalized yet',
   min_lvl tinyint NOT NULL
      CHECK (min_lvl >= 10),
   max_lvl tinyint NOT NULL
      CHECK (max_lvl <= 250)
*/
/*基本报文格式表*/
drop table tblBaseMsgFormat
create table tblBaseMsgFormat
(
	id  int
	primary key,
	stor_id  int ,
	alig  int ,
	fillchar  char ,
	lentype  int ,
	maxlen  int ,
	splittype  int ,
	splitstr  varchar(50),
	name  varchar (50) 
	unique,
	remark  varchar(500),	
)