#include <iostream>
#include <string>

//두 문자열의 자릿수와 부호를 구해준다
void za_lit_su(std::string* a, std::string* b, int* ca, int* cb);

//문자열 a와 문자열 b를 더해서 반환
std::string calc_plus(std::string a, std::string b);

//문자열 a와 문자열 b를 빼서 반환
std::string calc_minus(std::string a, std::string b);

//문자열 a와 문자열 b를 곱해서 반환
std::string calc_multi(std::string a, std::string b);


int main()
{
    std::string a, b;

    std::cin >> a;
    std::cin >> b;
    printf("%s\n%s\n%s", calc_plus(a, b).c_str(), calc_minus(a, b).c_str(), calc_multi(a, b).c_str());
}





void za_lit_su(std::string* a, std::string* b, int* ca, int* cb) {      //a와 b의 자릿수를 맞추기 위해 포인터로 받아온다
    int i;                                                              //값을 직접 바꾸기 위해서
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
                    i = a.substr(1) >= b.substr(1) ? 0 : 1;
                }
                if (i == 0) {
                    for (i = 0; i < size; i++) {
                        if (i == 0) {
                            if (a[0] == 'z') continue;              //위 if문에 이미 걸러지는건데 쓸데없이 넣어짐 졸았나?
                            answer += a[0];
                            continue;
                        }else
                        if (b[i] == 'z') {
                            answer += a[i];
                            continue;
                        }else
                        if (b[i] == '-') {
                            answer += a[i];
                            continue;
                        }else answer += a[i] - b[i] + '0';      //문자형으로 저장되어있어 원하는 값을 얻기위해 '0'만큼 더해준다
                    }
                    i = 0;                                      //오류 방지를 위해
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
                        }else
                        if (a[i] == 'z') {
                            answer += a[i];
                            continue;
                        }else
                        if (a[i] == '-') {
                            answer += b[i];
                            continue;
                        }else answer += b[i] - a[i] + '0'; //문자형으로 저장되어있어 원하는 값을 얻기위해 '0'만큼 더해준다
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
                        answer[i - 1] -= 1;
                        answer[i] += 10;
                    }
                }
                
                if (answer.length() > 1 && answer[i - 2] < '0') continue;

                if (i == size) {
                    if (answer.length() != 2 && answer[0] != '0') continue;
                    break;
                }
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
                        answer[i - 1] -= 1;
                        answer[i] += 10;
                    }
                }
                if (i == size) break;
            } while (true);
        }
        return answer;
    }
} 




std::string calc_minus(std::string a, std::string b) {      //calc_plus의 반대
    std::string answer; //출력할 값
    int i = 0;
    int size = 0;
    int ca = 0;
    int cb = 0;
    std::string zero;
    zero += '0';
    
    za_lit_su(&a, &b, &ca, &cb);

    if (ca + cb == 1) {

        size = a.length(); //자릿수를 저장

        //각 문자열의 자리끼리 더하기
        if (ca == 0) {
            for (i = 0; i < size; i++) {
                if (a[i] == 'z' || b[i] == 'z') {
                    if (b[i] == '-') continue;           //둘중 a는 공백이고 b는 '-' 기호일때
                    answer += a[i] + b[i] - 'z';
                    continue;
                }

                if (b[i] == '-') {
                    answer += a[i];
                    continue;

                }

                answer += a[i] + b[i] - '0'; //문자형으로 저장되어있어 원하는 값을 얻기위해 '0'만큼 뺴준다
            } //ex) '1' + '3' == 49 + 51 == 'd' 이기에

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
        else {                  //음수인경우

            for (i = 0; i < size; i++) {
                if (i == 0) {
                    answer += '-';
                    continue;
                }else
                if (a[i] == 'z' || b[i] == 'z') {
                    answer += a[i] + b[i] - 'z';
                    continue;
                }else
                if (a[i] == '-' || b[i] == '-') {
                     answer += a[i] + b[i] - '-';
                     continue;
                }else answer += a[i] + b[i] - '0'; //문자형으로 저장되어있어 원하는 값을 얻기위해 '0'만큼 뺴준다
            }

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
    }
    else {

        size = a.length(); //자릿수를 저장

        //각 자릿수 더하기
        if (ca + cb == 0) {       // 양수인경우
            if (a.compare(b) >= 0) {            //a의 절댓값이 큰 경우
                for (i = 0; i < size; i++) {
                    if (b[i] == 'z') {
                        answer += a[i];
                        continue;
                    }
                    answer += a[i] - b[i] + '0';
                }
            }
            else {                              //a의 절댓값이 낮은 경우
                for (i = 0; i < size; i++) {
                    if (a[i] == 'z') {
                        answer += b[i];
                        continue;
                    }
                    answer += b[i] - a[i] + '0';
                }
                answer = '-' + answer;
            }
        }
        else {              //음수인경우

            if ((a.substr(1)).compare(b.substr(1)) >= 0) {            //a의 절댓값이 큰 경우
                for (i = 0; i < size; i++) {
                    if (b[i] == 'z') {
                        answer += a[i];
                        continue;
                    }else 
                    if (b[i] == '-') {
                        answer += a[i];
                        continue;
                    }else answer += a[i] - b[i] + '0';
                }
            }
            else {                              //a의 절댓값이 낮은 경우
                for (i = 0; i < size; i++) {
                    if (a[i] == 'z') {
                        answer += b[i];
                        continue;
                    }else
                    if (b[i] == '-') {
                        answer += b[i];
                        continue;
                     }else answer += b[i] - a[i] + '0';
                }
            }
        }
    }

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
                    answer[i - 1] -= 1;
                    answer[i] += 10;
                }
            }

            if (answer[i - 1] < '0') continue;

            if (i == size) {
                break;
            }

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
                    answer[i - 1] -= 1;
                    answer[i] += 10;
                }
            }

            if (i == size) break;

        } while (true);
    }
    return answer;
}




std::string calc_multi(std::string a, std::string b) {
    std::string answer = a;
    std::string i = b;
    std::string one;
    std::string zero;
    zero += '0';
    one += '1';
    bool ca = true;                 //깨닳음을 얻고 bool형으로 선언
    bool cb = true;
    ca = a[0] != '-' ? 1 : 0;
    cb = b[0] != '-' ? 1 : 0;

    if (a == calc_minus(one, one) || b == calc_minus(one, one)) {       //둘중 하나라도 0일때
        answer = calc_minus(one, one);                                  //calc_minus(one, one) == 0
    } else                                                              //좀더 일찍 떠올렸으면 전역변수에 선언해서 편하게 했을텐데;;
    if (ca + cb == 2) {             //둘다 양수일때
        do {
            if (i != calc_minus(one, one)) break;
            i = calc_minus(i, one);
            answer = calc_plus(answer, b);
        } while (true);
    }else
    if (ca + cb == 0) {             //둘다 음수일때
        answer.erase(0, 1);
        b.erase(0, 1);              //'-'기호 제거
        i.erase(0, 1);
        do {
            if (i != calc_minus(one, one)) break;
            i = calc_minus(i, one);
            answer = calc_plus(answer, b);
        } while (true);
    }
    else {
        //'-'기호 제거
        if (ca == 0) {
            answer.erase(0, 1);
        }
        else {
            b.erase(0, 1);
            i.erase(0, 1);
        }

        do {
            if (i != calc_minus(one, one)) break;
            i = calc_minus(i, one);
            answer = calc_plus(answer, b);
        } while (true);
        answer = '-' + answer;
    }
    return answer;
}