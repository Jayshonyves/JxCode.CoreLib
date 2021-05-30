#include "../CoreLib/Events.hpp"

#include <iostream>

using namespace JxCoreLib;

class TestEvents
{
public:
    int cb_index;

    Action<int> e;
    void lambda_inst(int c) {
        std::cout << "lambda_inst callback" << std::endl;
    }
    void bind_inst(int c) {
        std::cout << "bind_inst callback" << std::endl;
    }
    static void static_method(int c) {
        std::cout << "static_method callback" << std::endl;
    }

    TestEvents()
    {
        //��̬lambda���ַ�ʽ
        e.AddListener([](int c) { std::cout << "static lambda1 callback" << std::endl; });
        e += [](int c) { std::cout << "static lambda2 callback" << std::endl; };

        //��̬����
        e += static_method; //�� e.AddListener(static_method);
        //e -= static_method; //�� e.RemoveListener(static_method);

        //������Ƴ��հ�lambda���������԰�lambda�йܸ�this��Ȼ�����ʵ���Ƴ�
        this->cb_index = e.AddListener(this, [this](int c) { this->lambda_inst(c); });
        //e.RemoveListenerByIndex(this->cb_index);

        //������Ƴ���Ա����
        e.AddListener(this, &TestEvents::bind_inst);
        //e.RemoveListener(this, &EventTest::bind_inst);

        //ִ��
        e.Invoke(3);

        //�Ƴ�ʵ���е������¼�
        e.RemoveListenerByInstance(this);

        //�Ƴ�ȫ���¼�
        e.RemoveAllListener();
    }
};

