#include<iostream>
#include<map>
#include<string>

using namespace std;

/*
* ================================================
* 题目要求： 
* 输入 R1 的路由表和 R2 发来的路由表，输出 R1 的新路由表。
* 
* R1路由表
* 网络   跳数    下一跳
* N1     1        R1
* N2     0        直接发送
* N3     6        R4 
* N4     8        R5
* 
* R2路由表
* 网络   跳数    下一跳
* N2     2        R5
* N3     3        R6
* N4     7        R7
* N5     3        R8
* ================================================
*/


//======================== 类与相关结构定义 ======================== 

// 想法是 网络号 -> (跳数， 下一跳)<用结构体进行定义括号内的玩意> 
struct target_net {
	int leap_cnt;
	string next_leap;

	target_net() { leap_cnt = 0; next_leap = ""; }
};

// 定义路由器 成员变量仅仅包括 名 + 路由表
class R_map {
private:
	int Rno;
	map<int, target_net> R;

public:
	// 2个重载R_map 适应多种初始化，但Rno必须先初始化
	R_map(int x) {
		Rno = x;
	}

	R_map(int x, map<int, target_net> r) {
		Rno = x;
		R = r;
	}

	// copy function
	R_map(const R_map& obj) {
		Rno = obj.getRno();
		R = obj.Rmap();
	}

	void load_map(map<int, target_net> info) {
		R = info;
	}

	int getRno() const {
		return Rno;
	}
	map<int, target_net> Rmap() const{
		return R;
	}

	// 打印map里的信息
	void print_info() {
		if (R.empty()) {
			cout << "R" + to_string(Rno) + "'s map is empty" << endl << endl;
			return;
		}
		cout << "R" + to_string(Rno) + " router table" << endl;
		cout << "Net     leap count      next leap" << endl;
		for (auto& [key, value] : R) {
			cout <<"N" << key << "       " << value.leap_cnt << "              " << value.next_leap << endl;
		}
		cout << endl;
	}

	// 更新路由表
	void update_table(int rno,map<int, target_net> otherR) {
		for (const auto& [key, value] : otherR) {
			if (!R.contains(key)) {
				target_net temp;
				temp.leap_cnt = value.leap_cnt;
				temp.next_leap = "R" + to_string(rno);

				R.insert({ key, temp });
			}

			else {
				target_net &a = R[key], b = value;
				if (a.leap_cnt > b.leap_cnt + 1) {
					a.leap_cnt = b.leap_cnt + 1;
					a.next_leap = "R" + to_string(rno);
				}
			}
		}
	}

	// 重载
	void update_table(R_map t) {
		map<int, target_net> otherR = t.Rmap();
		update_table(t.getRno(), otherR);
	}
};



// ======================== 初始化： 可能做的有点草率，毕竟只是一次练习( ========================
// R1  table 写入  - 题目的要求
void init_R1(R_map& R1) {
	int net;
	target_net k;
	map<int, target_net> temp;

	k.leap_cnt = 1, k.next_leap = "R1";
	temp[1] = k;
	k.leap_cnt = 0, k.next_leap = "directly sending";
	temp[2] = k;
	k.leap_cnt = 6, k.next_leap = "R4";
	temp[3] = k;
	k.leap_cnt = 8, k.next_leap = "R5";
	temp[4] = k;
	R1.load_map(temp);
}
// R2  table 写入
void init_R2(R_map& R2) {
	int net;
	target_net k;
	map<int, target_net> temp;

	k.leap_cnt = 2, k.next_leap = "R5";
	temp[2] = k;
	k.leap_cnt = 3, k.next_leap = "R6";
	temp[3] = k;
	k.leap_cnt = 7, k.next_leap = "R7";
	temp[4] = k;
	k.leap_cnt = 3, k.next_leap = "R8";
	temp[5] = k;
	R2.load_map(temp);
}


// ========================  main负责测试 ========================
int main() {
	R_map R1(1);
	R_map R2(2);

	// 测试空状态
	R1.print_info();
	R2.print_info();

	// 初始化R1
	init_R1(R1);
	R1.print_info();
	
	// 初始化R2
	init_R2(R2);
	R2.print_info();

	// 更新测试
	R1.update_table(R2);
	cout << "After updating ..." << endl;
	R1.print_info();

	return 0;
}