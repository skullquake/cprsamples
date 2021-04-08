#include<iostream>
#include<chrono>
#include"cpr/cpr.h"
#include"json/nlohmann/json.hpp"
#include"ctpl/ctpl_stl.h"
int main(void){
	auto tik=std::chrono::high_resolution_clock::now();
	//curl -H "Content-Type: application/json" --data '{"foo":"bar"}' http://www.httpbin.org/post
	auto work=[](int id){
		std::cout<<"thread["<<id<<"]:start"<<std::endl;
		nlohmann::json jreq;
		jreq["foo"]="bar";
		cpr::Response r=cpr::Post(
			cpr::Url{"http://www.httpbin.org/post"},
			cpr::Body{jreq.dump()},
			cpr::Header{{"Accept","application/json"}},
			cpr::Header{{"Content-Type","application/json"}}
		);
		auto jres=nlohmann::json::parse(r.text);
		//std::cout<<jres.dump(4)<<std::endl;
		std::cout<<"thread["<<id<<"]:end"<<std::endl;
	};
	ctpl::thread_pool p(8);
	for(int i=0;i<8;i++)p.push(std::ref(work));
	p.stop(true);
	auto tok=std::chrono::high_resolution_clock::now();
	auto dur=(tok-tik).count();
	//std::cout<<"Duration: "<<dur<<" us"<<std::endl;
	std::cout<<"Duration: "<<dur/1000000<<" ms"<<std::endl;
}
