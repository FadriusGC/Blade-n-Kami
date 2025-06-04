#pragma once
#include <string>
class InputHandler {
public:
    // �������� ����� ��� ��������� ��������� ����� �� ������������
    // ���������:
    // prompt - ��������� ��� ������������ (�������������)
    // clearInputBuffer - ����� �� ������� ����� ����� ����� �������� (�� ��������� true)
    static int getIntInput();

private:
    // ��������������� ����� ��� ������� cin �� ������������� �����
    static void clearInputStream();

    // ��������, �������� �� ������ �������� ����� ������
    static bool isValidInteger(const std::string& str);
};