#pragma once
#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <list>

//��������� ��������� ��������
class State
{
public:
   std::string m_id; //���������� ������������� ���������

   State() { m_id = ""; }                                                  //����������� �� ��������� ����������� ��������� ������ id
   State(std::string id) { m_id = id; }                                    //���������� � ����������� ����������� ��������� id �� ������� ������
   State& operator=(const State& obj) { m_id = obj.m_id; return *this; }   //�������� ������������, ���������� id ������� obj � ������ this
   bool operator==(const State& obj) { return m_id == obj.m_id; }          //�������� ���������, ������������ id ���� ���������
   friend bool operator<(const State& obj1, const State& obj2);            //�������� ��������� "������", ������������ id ���� �������� � ���. ��������� <
   ~State() {}
};

//��������� ��������� �� �������
typedef State(*funct_ptr)();

// ����������� ����� "�������� ����������� ����������"
class det_analizer
{
public:
   /*
   * @brief ����������� ������� �������� - ��������� �������� �� ������� ��������� � ����������� �� �������� �������
   */
   virtual void parse();

   //������������ "���������� �������" � "�������"
   enum class symbolLexem;
   enum class Lexem;

   //��������� inp_symbol - ������������ ������ � ��� �������������� � �������� ��������� ��������
   struct inp_symbol
   {
      int s_value; //ASCII - ��� �������
      symbolLexem s_class; //�������������� � ��������
   };


protected:
   std::map<State, std::map<symbolLexem,funct_ptr>> m_func_table;    //������� ��������� �����������
   std::list<std::tuple<Lexem, long long int, size_t>> m_lexem_list; //������ ������ �����������
   std::map<std::string, double> m_name_table;                       //������� ���
   State m_curr_state;                                               //������� ��������� �����������
   inp_symbol m_curr_sym;                                            //������� ������� ������
   std::fstream m_file;                                              //������� �������� �����


   /*
   * @brief ����������� ������� ��������������. ������� �� ���������, ������������ � ����������� ������ ���������������.
   * @param int sym
   * @returns ������ ��������� inp_symbol
   */
   virtual inp_symbol transliterator(int sym) = 0;
 
};
