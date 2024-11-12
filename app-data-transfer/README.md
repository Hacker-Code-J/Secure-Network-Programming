# Practice 1-1 데이터 전송

- 가변길이 데이터 전송 후 접속 정상 종료
  - 일종의 가변 길이 데이터 전송 방식
  - EOR로 특별한 데이터 패턴을 사용하는 대신 연결 종료를 사용
- 목적
  - 가변길이 데이터를 전송한 후 접속을 정상종료하여 메시지 전송의 완료 표시
- 구성
  - server_closeontransfer.c
  - client_closeontransfer.c

# Practice 1-2 데이터 전송

- 고정길이 데이터 송수신
  - 서버와 클라이언트에서 고정길이 데이터를 송수신
- 목적
  - 고정 길이 메시지 송수신 방법을 통하여 메시지의 경계를 표현
- 구성
  - server_fixed.c
  - client_fixed.c
 
# Practice 1-3 데이터 전송

- 가변길이 데이터 송수신
  - 전송되는 데이터의 경계를 표현하기 위해 EOR(End of Record) 정의
- 목적
  - 가변 길이 메시지를 송수신하기 위해 EOR을 정의하여 메시지 경계 표시
    - `\n`을 EOR로 정의
    - 일반적으로 `\r\n` 또는 `\n`을 EOR로 정의함
- 구현
  - 1-byte씩 읽어서 EOR인지 확인하는 방법도 있으나 성능이 떨어짐
  - 한번에 많은 데이터를 수신 버퍼에서 읽어 1-byte씩 리턴해주는 함수 구현
- 구성
  - server_variable.c
  - client_variable.c

# Practice 1-4 데이터 전송

- 고정길이 + 가변길이 데이터 송수신
  - 고정길이로 전송되는 데이터를 통해 이후 전송될 가변 길이 데이터의 길이를 명시
- 목적
  - 고정길이 데이터를 통해, 이후 전송될 가변길이 데이터의 길이를 표시
- 구성
  - server_fixedvariable.c (server_fv.c)
  - client_fixedvariable.c (client_fv.c)

# Practice 2-1 데이터 전송
- 고정길이 데이터 전송 방법을 이용한 채팅 프로그램
  - server_fixed_chat.c
  - client_fixed_chat.c
- 채팅 ID는 서버와 클라이언트 모두 명령행 인자로 입력
- 항상 클라이어튼 -> 서버 -> 클라이언트 -> 서버 -> ... 순서로만 채팅 메시지를 입력하는 것으로 가정

# Practice 2-2 데이터 전송
- 고정길이 데이터 전송 방법을 이용한 채팅 프로그램
  - server_fixed_chat.c
  - client_fixed_chat.c
- 채팅 ID는 서버와 클라이언트 모두 명령행 인자로 입력
- 항상 클라이어튼 -> 서버 -> 클라이언트 -> 서버 -> ... 순서로만 채팅 메시지를 입력하는 것으로 가정

# Practice 2-3 데이터 전송
- 고정길이 + 가변길이 데이터 전송 방법을 이용한 채팅 프로그램
  - server_fv_chat.c
  - client_fv_chat.c
