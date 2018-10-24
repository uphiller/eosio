# addressbook
https://developers.eos.io/eosio-home/docs/data-persistence

## CMD
```

#컨트랙트 실행
./cleos.sh push action <컨트랙트계정> upsert '["<계정명>", "<계정명>", "liddell", "123 drink me way", "wonderland", "amsterdam"]' -p <계정명>@active

#데이터 확인
./cleos.sh get table <컨트랙트계정> <스코프> <테이블명> -k <계정명>

#컨트랙트 실행
./cleos.sh push action <컨트랙트계정> erase '["<계정명>"]' -p <계정명>@active


```

