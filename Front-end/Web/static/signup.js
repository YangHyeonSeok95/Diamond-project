let radioChange = () => {
    let selected = $('input[name="signup_by"]:checked').val();
    if(selected == "mobile"){
        $('#signup_info').innerHTML="<p>휴대폰 번호 본인 인증 후, 회원가입이 됩니다.</p>";
    }else if (selected == "email"){
        $('#signup_info').innerHTML="<p>이메일 본인 인증 후, 회원가입이 됩니다.<br><span class='text-warning'>이메일 인증 가입의 경우, 사육장 상태 알람 카톡 서비스는 제공되지 않습니다.</span><br><span class='text-info'>카톡 알람 서비스를 원하신다면 휴대폰 인증 가입을 이용하시거나<br>이메일 인증 가입 후, '내 정보'에서 휴대폰 정보를 추가해 주세요.</span></p>";
    }
}
