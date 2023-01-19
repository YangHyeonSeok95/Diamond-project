alter table tbl_community add commu_views number(12,0) default 0 not null;
alter table tbl_community add commu_like number(12,0) default 0 not null ;

commit;

alter table tbl_member add constraint mb_signup_type_ck check (mb_signup_type in ('D', 'N', 'K'));

commit;