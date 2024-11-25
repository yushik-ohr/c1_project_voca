20241118

!!! 실행 전: 상단 메뉴 바에서 -> 디버그 -> 디버그 속성 -> C/C++ -> SDL 검사 -> 아니요 !!!

암기 카드 게임 복습 완료 후 여러 번 N 입력해야 탈출 가능하던 오류 해결
memcard.h의 global variable 'int reviewCompleted'를 flag로 판단하도록 함

사용자 입력 값 유효성 검사 후 초기 화면으로 돌아가도록 개선

getValidInputInMemoryCardGame 함수 삭제, getVaildInput 재사용으로 개선

암기 카드 게임 복습 화면 별도로 구현 및 수정

메인 메뉴 화면 수정

---

20241116

프로젝트 directory의 .txt 파일로부터 영단어와 의미를 불러서 linked list에 저장하는 구조.

아마 Visual Studio 2022로 열어야 .txt 파일과 함께 정상 작동 함.
