#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char* str, int start, int end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void find_lexicographically_smallest(char* word) {
    int n = strlen(word);
    char result[51];
    strcpy(result, "z"); // ���� ū ���ĺ����� �ʱ�ȭ

    for (int i = 1; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            char temp[51];
            strcpy(temp, word);

            // ù ��° �κ� ������
            reverse(temp, 0, i - 1);
            // �� ��° �κ� ������
            reverse(temp, i, j - 1);
            // �� ��° �κ� ������
            reverse(temp, j, n - 1);

            if (strcmp(temp, result) < 0) {
                strcpy(result, temp);
            }
        }
    }

    printf("%s\n", result);
}

int main() {
    char word[51];
    scanf_s("%50s", word);
    find_lexicographically_smallest(word);
    return 0;
}
