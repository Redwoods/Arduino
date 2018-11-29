/*
 예제 9.3
 DS1302 RTC 모듈을 이용하여 시간 정보 읽기
*/

// DS1302 라이브러리를 불러온다
#include <DS1302.h>

// DS1302 핀 설정
const int CEPin = 5;
const int IOPin = 6;
const int CLKPin = 7; 

// DS1302 모듈을 rtc 오브젝트로 설정
DS1302 rtc(CEPin, IOPin, CLKPin);

// DS1302에서 읽어낸 데이터 중 day 값으로 요일을 설정한다
String dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sunday";
    case Time::kMonday: return "Monday";
    case Time::kTuesday: return "Tuesday";
    case Time::kWednesday: return "Wednesday";
    case Time::kThursday: return "Thursday";
    case Time::kFriday: return "Friday";
    case Time::kSaturday: return "Saturday";
  }
  return "(unknown day)";
}

void setup() {
  // 시리얼 통신 설정
  Serial.begin(9600);
  // rtc에 쓰기방지 OFF, 정지기능 OFF
  rtc.writeProtect(false);
  rtc.halt(false);

  // 입력하고자 하는 시간을 적는다
  // 2015년 8월 15일 0시 0분 0초 토요일 로 설정한다
  Time t(2015, 8, 15, 00, 00, 00, Time::kSaturday);

  // 현재의 시간을 DS1302에 입력한다
  rtc.time(t);
}

void loop() {
  // DS1302로 부터 현재 시간을 읽어온다
  Time t = rtc.time();

  // day 데이터를 요일로 변경한다
  const String day = dayAsString(t.day);

  // 현재 요일 날짜 시간 순서대로 시리얼 통신으로 출력한다.
  Serial.print(day.c_str());
  Serial.print(" ");
  Serial.print(t.yr);
  Serial.print("-");
  Serial.print(t.mon);
  Serial.print("-");
  Serial.print(t.date);
  Serial.print(" ");
  Serial.print(t.hr);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(":");
  Serial.println(t.sec);
  
  delay(1000);
}
