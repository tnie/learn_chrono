#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;
//using namespace chrono;

void test_duration();
void test_time_point_clock();

int main()
{
    test_duration();
    auto str = R"(
*****************************************************************************
duration �ĸ����Ϊ�������� time_t �� clock �������ã����Ի������Եı߽硣
    duration ֻҪ������ֵ����λ�ͺ�������⡣
*****************************************************************************
)";
    cout << str << endl;
    test_time_point_clock();
    return 0;
}


void test_duration()
{
    auto twoseconds = chrono::duration<int>(2);
    //auto twoseconds = chrono::seconds(2);
    chrono::milliseconds alias = twoseconds;    // �ⶼ��-�����������
    {
        alias = twoseconds;     // �;��ȸ�ֵ���߾��ȿ���
        //twoseconds = alias;     // �߾��ȸ�ֵ���;��ȱ�����ʽת��
    }

    cout << "2s has " << twoseconds.count() << " seconds" << endl;
    cout << "2s has " << alias.count() << " milliseconds" << endl;
    alias = twoseconds * 2;    // �ⶼ��
    cout << "4s has " << alias.count() << " milliseconds" << endl;
    alias = twoseconds / 2;    // �ⶼ��
    cout << "1s has " << alias.count() << " milliseconds" << endl;
    alias = twoseconds / 4;    // �ⶼ�У�����Ǵ����
    /*����Ҳ���Ǹ��ȳ˺�����ȳ���˵�����*/
    cout << "0.5s has " << alias.count() << " milliseconds" << endl;
    {
        // �Զ���ʱ����������
        typedef chrono::duration<double, ratio<1, 2>> halfseconds;
        auto var = halfseconds(2.5);    // 1.25 ��
        cout << "1.25s has " << var.count() << " halfseconds" << endl;
        //alias = var; // ��Ҫ��ʾת��
        alias = chrono::duration_cast<chrono::milliseconds> (var);
        cout << "1.25s has " << alias.count() << " milliseconds" << endl;

    }
    {
        chrono::milliseconds diff = alias - twoseconds;
        cout << "diff(milli) is: " << diff.count() << endl;
    }
    {
        chrono::seconds diff = chrono::duration_cast<chrono::seconds>(alias - twoseconds);      // ������ʽת��
        cout << "diff(seconds) is: " << diff.count() << endl;
    }

    cout << "sleep 2s ..." << endl;
    //this_thread::sleep_for(twoseconds);
    this_thread::sleep_for(2s); //TODO  �ⶼ�а����������ʵ�ֵģ�
    cout << "END" << endl;

}

void test_time_point_clock()
{
    {
        chrono::time_point<chrono::steady_clock> t1 = chrono::steady_clock::now();
        this_thread::sleep_for(2s);
        auto t2 = chrono::steady_clock::now();
        chrono::steady_clock::duration diff = t2 - t1;
        cout << setw(20) << "diff(nano) is: " << diff.count() << endl;   // 2s �������ϸ������ϵ� 2*10^9 ����
        cout << setw(20) << "now(nano) is: " << t2.time_since_epoch().count() << endl;  //  TODO steady_clock ���Ǵ� 1970 ������
        chrono::steady_clock;   // û�� to_time_t()/fromw_time_t()
        chrono::system_clock::now();
    }

    {
        auto t3 = chrono::system_clock::now();  // �鿴�ײ�ʵ�֣����� system_clock �� steady_clock ���ȵ�100 ��
        cout << setw(20) << "now(nano*100) is: " << t3.time_since_epoch().count() << endl;
        cout << setw(20) << "now(time_t) is: " << chrono::system_clock::to_time_t(t3) << endl;

        {
            typedef chrono::duration<int, ratio<60 * 60 * 24>> days_type;
            //days_type days = t3.time_since_epoch();     // TODO why?
            days_type days = chrono::duration_cast<days_type>(t3.time_since_epoch());
            cout << setw(20) << "now(days) is: " << days.count() << endl;
            auto days_point = chrono::time_point_cast<days_type>(t3);   // �������ȼ�
            cout << setw(20) << "now(days) is: " << days_point.time_since_epoch().count() << endl;
        }

    }

}