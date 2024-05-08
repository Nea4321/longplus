#include <iostream>
#include <string>


void za_lit_su(std::string* a, std::string* b, int* ca, int* cb);

//문자열 a와 문자열 b를 더해서 출력
std::string calc_plus(std::string a, std::string b);



int main()
{
    std::string a, b;

    std::cin >> a;
    std::cin >> b;
    printf("%s", calc_plus(a, b).c_str());
}





void za_lit_su(std::string* a, std::string* b, int* ca, int* cb) {
    int i;
    std::string sa = *a;
    std::string sb = *b;
    int size;
    if (sa[0] == '-') *ca += 1;
    if (sb[0] == '-') *cb += 1;

    if (sa.length() == sb.length()) {} //같을경우 넘기기
    else if (sa.length() > sb.length()) { //문자열 a가 문자열 b보다 자릿수가 클떄
        size = sa.length() - sb.length();
        for (i = 0; i < size; i++) //자릿수가 부족한 만큼 반복
            sb = 'z' + sb; //0번째 자리에 'z'을 삽입
    }
    else {
        size = sb.length() - (sa.length());
        for (i = 0; i < size; i++) //문자열 b가 문자열 a보다 자릿수가 클떄
            sa = 'z' + sa;
    }
    *a = sa;
    *b = sb;
}





std::string calc_plus(std::string a, std::string b) {
    std::string answer; //출력할 값
    int i = 0;
    int size = 0;
    int ca = 0;
    int cb = 0;

    za_lit_su(&a, &b, &ca, &cb);

    if (ca == 0 && cb == 0) { //문자열 a와 문자열 b가 모두 양수일때

        size = a.length(); //자릿수를 저장

        //각 문자열의 자리끼리 더하기
        for (i = 0; i < size; i++) {
            if (a[i] == 'z' || b[i] == 'z') {
                answer += a[i] + b[i] - 'z';
                continue;
            }
            answer += a[i] + b[i] - '0'; //문자형으로 저장되어있어 원하는 값을 얻기위해 '0'만큼 뺴준다
        } //ex) '1' + '3' == 49 + 51 == 'd' 이기에                                

        //10이 넘어가는 경우 정리
        do {
            //0번째가 넘어갈때 처리
            if (answer[0] > '9') {
                answer = 'z' + answer; //
                answer[0] = '1';
                answer[1] -= 10;
            }
            size = answer.length();
            for (i = size - 1; i > 0; i--) {
                if (answer[i] > '9') {
                    answer[i - 1]++;
                    answer[i] -= 10;
                }
            }
            if (i == 0) break;
        } while (true);
        return answer;
    }
    else if (ca == 1 && cb == 1) { //문자열 a와 문자열 b가 모두 음수일때

        size = a.length(); //자릿수를 저장

        //각 문자열의 자리끼리 더하기
        for (i = 0; i < size; i++) {
            if (i == 0) {
                answer += '-';
                continue;
            } else
            if (a[i] == 'z' || b[i] == 'z') {
                answer += a[i] + b[i] - 'z';
                continue;
            } else
            if (a[i] == '-' || b[i] == '-') {
                answer += a[i] + b[i] - '-';
                continue;
            } else
            answer += a[i] + b[i] - '0'; //문자형으로 저장되어있어 원하는 값을 얻기위해 '0'만큼 뺴준다
        } //ex) '1' + '3' == 49 + 51 == 'd' 이기에                                

        //10이 넘어가는 경우 정리
        do {
            //0번째가 넘어갈때 처리
            if (answer[1] > '9') {
                answer = '-' + answer; //
                answer[1] = '1';
                answer[2] -= 10;
            }
            size = answer.length();
            for (i = size - 1; i > 1; i--) {
                if (answer[i] > '9') {
                    answer[i - 1]++;
                    answer[i] -= 10;
                }
            }
            if (i == 1) break;
        } while (true);
        return answer;
    }
    else { //문자열 a와 문자열 b중 하나가 음수일때

        size = a.length(); //자릿수를 저장

        //각 문자열의 자리끼리 빼기
        if (ca == 0) {                          //문자열 a가 양수일때
            if (a[1] != 'z' && a[1] >= b[1] || a[0] != 'z') {       //문자열 a와 문자열 b의 절대값중 a가 더 큰경우를 찾는 작업
                if (a[0] == 'z' && a[1] == b[1]) {
                    i = a.erase(0, 1) >= b.erase(0, 1) ? 0 : 1;
                }
                if (i == 0) {
                    for (i = 0; i < size; i++) {
                        if (i == 0) {
                            if (a[0] == 'z') continue;
                            answer += a[0];
                            continue;
                        }else
                        if (b[i] == 'z') {
                            answer += a[i];
                            continue;
                        }
                        else
                            if (b[i] == '-') {
                                answer += a[i];
                                continue;
                            }
                            else
                                answer += a[i] - b[i] + '0'; //문자형으로 저장되어있어 원하는 값을 얻기위해 '0'만큼 더해준다
                    }
                }
            }
            else i = 1;

            if (i == 1) {                       //문자열 b의 절대값이 더 큰 경우
                for (i = 0; i < size; i++) {
                    if (i == 0) {
                        answer += '-';
                        continue;
                    }
                    else if (a[i] == 'z') {
                        answer += b[i];
                        continue;
                    }
                    else {
                        answer += b[i] - a[i] + '0';
                        continue;
                    }
                }
            }
        }
        else {
            if (b[1] != 'z' && b[1] >= a[1] || b[0] != 'z') {       //문자열 a와 문자열 b의 절대값중 a가 더 큰경우를 찾는 작업
                if (b[0] == 'z' && b[1] == a[1]) {
                    i = b.erase(0, 1) >= a.erase(0, 1) ? 0 : 1;
                }
                if (i == 0) {
                    for (i = 0; i < size; i++) {
                        if (i == 0) {
                            if (b[0] == 'z') continue;
                            answer += b[0];
                            continue;
                        }
                        else
                            if (a[i] == 'z') {
                                answer += a[i];
                                continue;
                            }
                            else
                                if (a[i] == '-') {
                                    answer += b[i];
                                    continue;
                                }
                                else
                                    answer += b[i] - a[i] + '0'; //문자형으로 저장되어있어 원하는 값을 얻기위해 '0'만큼 더해준다
                    }
                }
            }
            else i = 1;

            if (i == 1) {                       //문자열 b의 절대값이 더 큰 경우
                for (i = 0; i < size; i++) {
                    if (i == 0) {
                        answer += '-';
                        continue;
                    }
                    else if (b[i] == 'z') {
                        answer += a[i];
                        continue;
                    }
                    else {
                        answer += a[i] - b[i] + '0';
                        continue;
                    }
                }
            }
        }

        //10이 넘어가는 경우 정리
        if (answer[0] != '-') {     //양수일때
            do {
                //0번째가 넘어갈때 처리
                if (answer[0] < '1') {
                    answer[1] += '0' - answer[0];
                    answer.erase(0, 1);
                }
                size = answer.length();
                for (i = 1; i < size; i++) {
                    if (answer[i] < '0') {
                        answer[i + 1] += '0' - answer[i];
                        answer[i] += 10;
                    }
                }
                if (i == size) break;
            } while (true);
        }
        else {                      //음수일때
            do {
                //0번째가 넘어갈때 처리
                if (answer[1] < '1') {
                    answer[2] += '0' - answer[1];
                    answer = answer.erase(1, 1);
                }
                size = answer.length();
                for (i = 2; i < size; i++) {
                    if (answer[i] < '0') {
                        answer[i + 1] += '0' - answer[i];
                        answer[i] += 10;
                    }
                }
                if (i == size) break;
            } while (true);
        }
        return answer;
    }
}