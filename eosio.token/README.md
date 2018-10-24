# eosio.token
https://developers.eos.io/eosio-home/docs/token-contract

## CMD
```

# 계정 토큰 정보
./cleos.sh get currency stats <컨트랙트 계정> <토큰 심볼>

# 토큰 할당
./cleos.sh push action <컨트랙트 계정> create '["<계정>", "1000000000.0000 SYS", "memo"]' -p <컨트랙트 계정>@active

# 토큰 생성
./cleos.sh push action <컨트랙트 계정> issue '["<계정>", "100.0000 SYS", "memo"]' -p <컨트랙트 계정>@active

#잔액 확인
./cleos.sh get table <컨트랙트 계정> <계정> accounts

#토큰 발행
./cleos.sh push action <컨트랙트 계정> issue '["<계정>", "100.0000 SYS", "memo"]' -p <계정 오너>@active

# 토큰 전송
./cleos.sh push action <컨트랙트 계정> transfer '[ "<from 계정>", "<to 계정>", "25.0000 SYS", "memo" ]' -p <from 계정>@active

#unlock
./cleos.sh push action <컨트랙트 계정> unlock '["계정"]' -p <계정 오너>@active


```
