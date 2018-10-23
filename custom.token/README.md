# custom.token

## CMD
```
#key 생성
./cleos.sh create key --to-console

#계정연동
./cleos.sh wallet import --private-key <프라이빗키>

#계정추가
./cleos.sh system newaccount --stake-net '3 EOS' --stake-cpu '3 EOS'  --buy-ram-kbytes 3  <내 account> <새로운계정> <퍼블릭키> -p <내 account>@active

#램추가
./cleos.sh system buyram <내 account> <내 account> '30.0000 EOS'

#컨트랙트 배포
./cleos.sh set contract jungle111112 ~/eos/contracts/eosio/eosio.token

# 계정 토큰 정보
./cleos.sh get currency stats <컨트랙트 계정> SYS

# 토큰 할당
./cleos.sh push action <컨트랙트 계정> create '["<계정>", "1000000000.0000 SYS", "memo"]' -p <컨트랙트 계정>@active

# 토큰 생성
./cleos.sh push action <컨트랙트 계정> issue '["<계정>", "100.0000 SYS", "memo"]' -p <컨트랙트 계정>@active

#잔액 확인
./cleos.sh get table <컨트랙트 계정> <계정> accounts

#토큰 발행
./cleos.sh push action jungle111112 issue '["jungle111114", "100.0000 SYS", "memo"]' -p jungle111113@active

#unlock
./cleos.sh push action jungle111112 unlock '["jungle111114"]' -p jungle111112@active


```
