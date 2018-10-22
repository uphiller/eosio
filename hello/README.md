# hello
https://developers.eos.io/eosio-home/docs/your-first-contract

##CMD
`
//지갑생성
./cleos.sh wallet create --to-console

//지갑잠김 해제
./cleos.sh wallet unlock

//key 생성
./cleos.sh create key --to-console

//계정연동
./cleos.sh wallet import --private-key {{ private key }}

//컨트랙트 빌드
eosio-cpp -o ${contract}.wast ${contract}.cpp --abigen

`
