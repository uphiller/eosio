# hello
https://developers.eos.io/eosio-home/docs/your-first-contract

## CMD
```
#지갑생성
./cleos.sh wallet create --to-console

#지갑잠김 해제
./cleos.sh wallet unlock

#key 생성
./cleos.sh create key --to-console

#계정연동
./cleos.sh wallet import --private-key {{ private key }}

#컨트랙트 빌드
eosio-cpp -o ${contract}.wast ${contract}.cpp --abigen

#램추가
./cleos.sh system buyram <내 account> <내 account> '1.0000 EOS'

#계정추가
./cleos.sh system newaccount --stake-net '3 EOS' --stake-cpu '3 EOS'  --buy-ram-kbytes 3  <내 account> <새로운계정> EOS8RjEVRnpq8pGsRtWTDhbMjrmbH2CWWXh2z2AbpP5RxHtYbBZB5 -p <내 account>@active

#컨트랙트배포
./cleos.sh set contract <배포 account> ~/eos/contracts/hello

#컨트랙트 실행
./cleos.sh push action helloaa12345  hi '["<account>"]' -p <account>@active

#지갑 비번 분실

#cpu 사기

```
