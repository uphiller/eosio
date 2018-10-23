# addressbook
https://developers.eos.io/eosio-home/docs/data-persistence

## CMD
```

#컨트랙트 실행
./cleos.sh push action addressbook1 upsert '["<계정명>", "<계정명>", "liddell", "123 drink me way", "wonderland", "amsterdam"]' -p <계정명>@active

#데이터 확인
./cleos.sh get table <컨트랙트계정> <스코프> people -k junglpreiner

#컨트랙트 실행
./cleos.sh push action <컨트랙트계정> erase '["junglpreiner"]' -p junglpreiner@active


```
