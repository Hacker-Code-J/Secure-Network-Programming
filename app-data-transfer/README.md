# Practice 1 데이터 전송

- 가변길이 데이터 전송 후 접속 정상 종료
  - 일종의 가변 길이 데이터 전송 방식
  - EOR로 특별한 데이터 패턴을 사용하는 대신 연결 종료를 사용
- 목적
  - 가변길이 데이터를 전송한 후 접속을 정상종료하여 메시지 전송의 완료 표시
- 구성
  - server_closeontransfer.c
  - client_closeontransfer.c