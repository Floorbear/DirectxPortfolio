# 던전앤파이터 모작 프로젝트

본 프로젝트는 던전앤파이터를 기반으로 제작된 개인 포트폴리오 프로젝트로 원작의 전투 시스템과 게임 구조를 직접 분석하고 구현했습니다.

## 개요

이 프로젝트의 목표는 던전앤파이터의 핵심 요소인 타격감, 액션 시스템, 아바타 시스템을 실제 게임 수준으로 구현하여 게임 개발 역량을 강화하는 것입니다.

## 영상 및 시연

- [YouTube 시연 영상 링크](<https://www.youtube.com/watch?v=ECLa2Q2OpWU&ab_channel=Bear>)

## 설치 및 실행

- [다운 링크](<https://drive.google.com/file/d/15mmvsJWkaX7NokR3OGf7nvwFEX5PLdE9/view?usp=sharing>)
- 실행 : DirectxPortfolio\Bin\Release\x64\GameEngineApp.exe 로 실행

---

##  기술소개서

- [다운](https://drive.google.com/file/d/1Ia1EGuGqAz2j_CBeaNlbsc76H71lMs5a/view?usp=sharing)

## 기술 스택

- **C++**
- **DirectX 11**

## 주요 구현 시스템

### 액터 클래스 설계

- Player와 Monster 클래스의 상속 구조 설계
- 공격 판정 및 렌더링 시스템 구축

### 렌더링 및 깊이 정렬 (Z-sort)

- Y축 위치값을 Z축에 복사하여 렌더링 순서 결정
- Z축 깊이에 따라 오브젝트 정렬 후 화면 렌더링

### 전투 시스템

#### 히트 판정 처리
- 공격 충돌 타입 확인 및 Z축 거리 조건을 통한 정확한 히트 판정
- 중복 히트 방지 처리

#### 히트 스탑 구현
- 공격 및 피격 시 `HitStopTime` 적용
- `HitStopTime`이 진행되는 동안 특정 상태(슈퍼아머, 출혈 제외)를 제외한 모든 행동 정지

#### 출혈 상태 효과 구현
1. 공격 성공 시 일정 확률로 출혈 상태 발생
2. 출혈 지속 시간 동안 도트 데미지 및 이펙트 처리

#### 히트 상태 관리 (Stagger, Airborne, Down)
- 상태별 전용 애니메이션 및 반응 처리
- 다운 상태에서 일정 시간 후 자동 기상 + 무적 시간 부여

#### 슈퍼아머 로직
- 슈퍼아머 상태 여부에 따른 상태 전이 제어

### 몬스터 AI 및 FSM

- 공통 FSM 상태 구조 설계
- 몬스터 고유 행동 패턴 구현

### 스킬 시스템

- 플레이어와 몬스터의 FSM 기반 스킬 실행 구조
- 각 스킬에 따른 특수 효과 및 연출 구현

### 아바타 시스템

- 다양한 아바타 교체 기능 구현
- 실시간 애니메이션 변경 로직 구성

## 작성자

- 이메일: floorbear2723@gmail.com
