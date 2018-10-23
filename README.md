# eosio

##cmd
```
##지갑 생성
./cleos.sh wallet create --to-console

#계정 확인
./cleos.sh get account <계정명>

#key 생성
./cleos.sh create key --to-console

#계정연동
./cleos.sh wallet import --private-key <프라이빗키>

#계정추가
./cleos.sh system newaccount --stake-net '3 EOS' --stake-cpu '3 EOS'  --buy-ram-kbytes 3  <내 account> <새로운계정> <퍼블릭키> -p <내 account>@active

#램추가
./cleos.sh system buyram <내 account> <내 account> '1.0000 EOS'

#컨트랙트 빌드
eosio-cpp -o ${contract}.wast ${contract}.cpp --abigen

#컨트랙트배포
./cleos.sh set contract <배포 account> <파일위치>

```
