# addressbook
https://developers.eos.io/eosio-home/docs/data-persistence

## CMD
```

#key 생성
./cleos.sh create key --to-console

#계정연동
./cleos.sh wallet import --private-key {{ private key }}

#계정추가
./cleos.sh system newaccount --stake-net '3 EOS' --stake-cpu '3 EOS'  --buy-ram-kbytes 3  <내 account> <새로운계정> EOS8RjEVRnpq8pGsRtWTDhbMjrmbH2CWWXh2z2AbpP5RxHtYbBZB5 -p <내 account>@active

#컨트랙트 빌드
eosio-cpp -o ${contract}.wast ${contract}.cpp --abigen

#컨트랙트배포
./cleos.sh set contract <배포 account> ~/eos/contracts/hello

#컨트랙트 실행
./cleos.sh push action addressbook1 upsert '["junglpreiner", "junglpreiner", "liddell", "123 drink me way", "wonderland", "amsterdam"]' -p junglpreiner@active

#데이터 확인
./cleos.sh get table addressbook1 addressbook1 people -k junglpreiner

#컨트랙트 실행
./cleos.sh push action addressbook1 erase '["junglpreiner"]' -p junglpreiner@active


```
