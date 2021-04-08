#include<iostream>
#include"cpr/cpr.h"
#include"json/nlohmann/json.hpp"
int main(void){
	//curl -H "Content-Type: application/json" --data '{"foo":"bar"}' http://www.httpbin.org/post
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
}
