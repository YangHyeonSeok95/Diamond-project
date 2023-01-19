CREATE TABLE tbl_community
(
    commu_seq        NUMBER(12, 0)    NOT NULL, 
    commu_title      VARCHAR2(30)     NOT NULL, 
    commu_type       CHAR(1)          NOT NULL, 
    commu_content    VARCHAR2(20)     NOT NULL, 
    mb_id            VARCHAR2(20)     NOT NULL, 
    commu_img        VARCHAR2(50)     NULL, 
    commu_update     date            default sysdate  NOT NULL , 
     PRIMARY KEY (commu_seq)
)
/

CREATE SEQUENCE tbl_community_SEQ
START WITH 1
INCREMENT BY 1;
/

CREATE OR REPLACE TRIGGER tbl_community_AI_TRG
BEFORE INSERT ON tbl_community 
REFERENCING NEW AS NEW FOR EACH ROW 
BEGIN 
    SELECT tbl_community_SEQ.NEXTVAL
    INTO :NEW.commu_seq
    FROM DUAL;
END;
/

--DROP TRIGGER tbl_community_AI_TRG; /

--DROP SEQUENCE tbl_community_SEQ; /

COMMENT ON COLUMN tbl_community.commu_seq IS '게시글 순번';
/

COMMENT ON COLUMN tbl_community.commu_title IS '게시글 제목';
/

/

COMMENT ON COLUMN tbl_community.commu_content IS '게시글 내용';
/

COMMENT ON COLUMN tbl_community.mb_id IS '회원 아이디';
/

COMMENT ON COLUMN tbl_community.commu_img IS '게시글 사진';
/

COMMENT ON COLUMN tbl_community.commu_update IS '게시글 수정일';
/

ALTER TABLE tbl_community
    ADD CONSTRAINT FK_tbl_community_mb_id_ck FOREIGN KEY (mb_id)
        REFERENCES tbl_member (mb_id) ON DELETE cascade;
/
alter table tbl_community add constraint commu_type_ck check(commu_type in ('f', 'q', 'n', 'u'));