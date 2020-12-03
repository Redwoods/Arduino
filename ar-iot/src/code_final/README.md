## 2020 final exam. resource

- Study 2 js and 3 html

### MongoDB
- db iot에서 최근 데이터 1000개를 csv 파일 (iot_s1000.csv)로 저장할 때의 명령은?
  - 저장할 데이터 항목: **시간,온도,습도,조도**

mongoexport -d=iot -c=sensors --sort="{_id: -1}" --limit=1000 --fields=date,temperature,humidity,luminosity --type=csv --out=iot_s1000.csv

- Query in Mongo shell (문서 검색)

  - db.sensors.count()  // sensors collection에 있는 도큐먼트 (문서)의 수
  - db.sensors.find().sort({_id: 1}).limit(10)   //오래된 document 10개 추출
  - db.sensors.find().sort({_id: -1}).limit(10)    //최근 document 10개 추출
  
  - db.sensors.find({date: {$gt:"2020-12-17 16:26:05"}} )    //특정 시간 이후 document 추출
  - db.sensors.find({temperature: {$gt: "25"}} )    // 온도가 25도를 넘는 document 추출
  
  

