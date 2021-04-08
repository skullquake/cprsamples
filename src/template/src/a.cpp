#include<iostream>
#include"cpr/cpr.h"
#include"json/nlohmann/json.hpp"
#include<thread>
int main(void){
	//curl -H "Content-Type: application/json" --data '{"foo":"bar"}' http://www.httpbin.org/post
	auto work=[](){
		nlohmann::json jreq;
		jreq["foo"]="bar";
		cpr::Response r=cpr::Post(
			cpr::Url{"http://www.httpbin.org/post"},
			cpr::Body{jreq.dump()},
			cpr::Header{{"Accept","application/json"}},
			cpr::Header{{"Content-Type","application/json"}}
		);
		auto jres=nlohmann::json::parse(r.text);
		std::cout<<jres.dump(4)<<std::endl;
	};
	std::thread t0(work);
	std::thread t1(work);
	std::thread t2(work);
	std::thread t3(work);
	t0.join();
	t1.join();
	t2.join();
	t3.join();
}
