# 3D 뱀서류
### NBC 무한성 탈출 1조 사이드 프로젝트




# 프로젝트 시작

```
1. git clone https://github.com/NBC-SideProject/Vampire-Survival.git

2. clone된 폴더에서 .uproject 더블클릭 > 언리얼 에디터 빌드 1회 실행

3. 빌드 완료 후 에디터 종료 > .uproject 연결프로그램 Rider로 다시 빌드

4. git lfs install 필수!
```





# Git branch 전략

## dev
개발 기준 브랜치
모든 서브 브랜치는 dev를 기준으로 branch 생성 > merge dev

## sub-branch
```bash
dev > switch -c <sub-branch-name>
```
## 서브 브랜치 네이밍
- feat/~
> feature, 기능구현 시

- fix/~
> fix, 기능 및 버그 수정 시

- chore/~
> 빌드 설정, 의존성 추가/삭제/수정 시

- docs/~
> 문서 추가/삭제/수정 시 

- refac/~
> 폴더구조, 기능 등 리팩토링 시

- ci/~
> workflow 수정 시

- hotfix/~
> dev branch 건너뛰고 즉시 main branch merge 필요할 경우

asd



# Git commit message

## Commit message 네이밍

- feat: ~
> feature, 기능구현 시

- fix: ~
> fix, 기능 수정 시

- chore: ~
> 빌드 설정, 의존성 추가/삭제/수정 시

- docs: ~
> 문서 추가/삭제/수정 시 

- refac/~
> 폴더구조, 기능 등 리팩토링 시

- ci: ~
> workflow 수정 시

- hotfix: ~
> dev branch 건너뛰고 즉시 main branch merge 필요할 경우



# Git LFS
GitHub 공식 문서 기준으로 LFS에 포함할 파일 타입은 git lfs track으로 등록하고, 그 결과 생성되는 .gitattributes도 커밋하는 것을 권장

```bash
git lfs install
```
