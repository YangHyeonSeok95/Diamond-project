-- 키트 추가
insert into tbl_kit(kit_name, cage_seq) values('DHT11_temp', 2);
commit;

-- 키트 센서값 추가 : cage_seq = 2
insert into tbl_kit_sensoring (kit_seq, sv_value, mb_id) 
values(
(select kit_seq from tbl_kit where kit_name = upper('dht11_humi') and cage_seq = 2),
2,'dodo');

-- 날짜 포맷팅
alter session set NLS_DATE_FORMAT='YYYY-MM-DD:HH24:MI:SS';
commit;

-- cage_seq  확인 : mb_id : dodo/ cage_seq : 1
select 
case
when 1 in (select cage_seq from tbl_cage where mb_id = 'dodo') then 'true'
else 'false'
end as cage_ck
from dual ;

-- 키트 목록 : cage_seq = 1
select distinct kit_seq from tbl_kit where cage_seq = 1;

-- 키트 센서값 및 정보 검색 by cage_seq :  cage_seq = 1
select * from 
(select t2.kit_name, t1.kit_seq, t1.sv_value, t1.sv_date from tbl_kit_sensoring t1
inner join tbl_kit t2
on t1.kit_seq = t2.kit_seq
where t2.cage_seq = 1) t3
where (t3.kit_seq, t3.sv_value) in (select kit_seq, max(sv_date) from tbl_kit_sensoring group by kit_seq);

select * from tbl_kit_sensoring 
where kit_seq in (select distinct kit_seq from tbl_kit where cage_seq = 1)
order by sv_date desc;

select sv_value
from tbl_kit_sensoring
where kit_seq = (select kit_seq from tbl_kit where kit_name = upper('dht11_temp')) and mb_id = 'dodo' and rownum = 1
order by sv_date desc;

select * from
(select * from tbl_kit_sensoring where (kit_seq, sv_date) in (
    select kit_seq, max(sv_date)
    from tbl_kit_sensoring group by kit_seq
) order by sv_date desc
) t
group by t.kit_seq;

-- 키트 별 최신 센서 값 : cage_seq = 1
select t1.kit_name, t2.sv_value
from (select t3.kit_seq, max(t3.sv_date) as sv_date, t4.kit_name 
from tbl_kit_sensoring t3, tbl_kit t4 
where t4.kit_seq=t3.kit_seq and t4.cage_seq = 1
group by t3.kit_seq, t4.kit_name) t1
inner join tbl_kit_sensoring t2 
on t1.kit_seq = t2.kit_seq
where t1.sv_date = t2.sv_date;

alter table tbl_pet modify pet_gender default 'n';
alter table tbl_pet modify pet_gender not null;
alter table tbl_pet add constraint pet_gender_ck check (pet_gender in ('f','m','n'));

update tbl_pet set pet_gender  = 'n' where pet_gender is null;

alter table tbl_member add mb_update date default sysdate not null;

commit;

select distinct pet_type from tbl_pet where cage_seq = 1;

-- cage_seq별 동물종과 이름(성별) 확인 : cage_seq = 1
select distinct t3.pet_type, listagg(t3.pet_info, '\n') WITHIN GROUP (ORDER BY t3.pet_info) AS PET_INFO
FROM (select PET_TYPE, (PET_NAME ||'('||
(CASE
WHEN PET_GENDER = 'f' THEN '♀'
WHEN PET_GENDER = 'm' THEN '♂'
ELSE '?'
END)
||')') as pet_info
from tbl_pet WHERE CAGE_SEQ=1) T3 GROUP BY T3.PET_TYPE;
select LISTAGG(T3.PET_TYPE,'/') WITHIN GROUP (ORDER BY T3.PET_TYPE) AS PET_TYPE FROM TBL_PET T3;


-- 키트 최신 값 조회 : cage_seq = 1 / kit_name = 'DHT11_TEMP'
select t1.sv_value
from tbl_kit_sensoring t1
inner join tbl_kit t2
on t1.kit_seq=t2.kit_seq
where t2.cage_seq = 1 and t2.kit_name = 'DHT11_TEMP' and t1.sv_date = (select max(sv_date) from tbl_kit_sensoring where kit_seq = t1.kit_seq);

-- 키트 이상 값 시간 조회
select (SYSDATE - t1.sv_date) AS HUMI_DELAY2
from tbl_kit_sensoring t1
inner join tbl_kit t2
on t1.kit_seq=t2.kit_seq
where t2.cage_seq = 1 and t2.kit_name = 'DHT11_HUMI'
and t1.sv_date = (select MAX(sv_date) from tbl_kit_sensoring where kit_seq = t1.kit_seq AND SV_VALUE > 50 AND SV_VALUE < 80)

union all

select (sysdate - kit_inst_date) as HUMI_DELAY from tbl_kit where cage_seq = 1 and kit_name = 'DHT11_HUMI'
and not exists
(select (SYSDATE - t1.sv_date) AS HUMI_DELAY2
from tbl_kit_sensoring t1
inner join tbl_kit t2
on t1.kit_seq=t2.kit_seq
where t2.cage_seq = 1 and t2.kit_name = 'DHT11_HUMI'
and t1.sv_date = (select MAX(sv_date) from tbl_kit_sensoring where kit_seq = t1.kit_seq AND SV_VALUE > 50 AND SV_VALUE < 80));


-- 엑추에이터 조회
select  t1.sv_value, T2.KIT_NAME
from tbl_kit_sensoring t1
inner join tbl_kit t2
on t1.kit_seq=t2.kit_seq
where t2.cage_seq = 1
and t1.sv_date = (select max(sv_date) from tbl_kit_sensoring where kit_seq = t1.kit_seq);


SELECT T3.CAGE_SEQ, T3.CAGE_NAME, LISTAGG(T3.PET_TYPE,'/') WITHIN GROUP (ORDER BY T3.PET_TYPE) AS PET_TYPE, LISTAGG(T3.PET_NAME,'/') WITHIN GROUP (ORDER BY T3.PET_NAME) AS PET_NAME
        FROM (SELECT T1.CAGE_SEQ, T1.CAGE_NAME,T2.PET_TYPE, LISTAGG(T2.PET_NAME,',') WITHIN GROUP (ORDER BY T2.PET_NAME) AS PET_NAME, T1.MB_ID
        FROM TBL_CAGE T1, TBL_PET T2
        WHERE T1.CAGE_SEQ = T2.CAGE_SEQ
        GROUP BY T1.CAGE_SEQ, T1.CAGE_NAME, T2.PET_TYPE, T1.MB_ID
        ORDER BY T1.CAGE_SEQ, COUNT(T2.PET_TYPE) DESC) T3
        WHERE T3.MB_ID = 'dodo'
        GROUP BY T3.CAGE_SEQ, T3.CAGE_NAME;
        
