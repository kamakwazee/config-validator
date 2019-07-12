
#include <iostream>

#include "jarvis_the_bee.h"
#include "file_inputter.h"
#include "rest_server.h"
#include "common.h"
#include <vector>

int main() {
    std::string sshPath = "/etc/ssh/sshd_config";
    std::string apachePath = "/etc/apache2/apache2.conf";
    std::string apache2Path = "/etc/apache2/conf-enabled/security.conf";
    std::string nginxPath = "/etc/nginx/nginx_config";
    std::string dovecotPath = "/etc/dovecot/conf.d/10-ssl.conf";
    std::string postfixPath = "/etc/postfix/main.cf";

    std::vector<ConfigSet> compare;
    compare.push_back(readFiles(SSH, sshPath));
    compare.push_back(readFiles(APACHE, apachePath));
    compare.push_back(readFiles(APACHE, apache2Path));
    compare.push_back(readFiles(NGINX, nginxPath));
    compare.push_back(readFiles(SSH, dovecotPath));
    compare.push_back(readFiles(SSH, postfixPath));


    std::vector<ConfigSet> baseline;
    std::string sshPathBaseline = "../../sec_configs/sshd_config";
    std::string apachePathBaseline = "../../sec_configs/apache2.conf";
    std::string apache2PathBaseline = "../../sec_configs/security.conf";
    std::string nginxPathBaseline = "../../sec_configs/nginx_config";
    std::string dovecotPathBaseline = "../../sec_configs/10-ssl.conf";
    std::string postfixPathBaseline = "../../sec_configs/main.cf";

    baseline.push_back(readFiles(SSH, sshPathBaseline));
    baseline.push_back(readFiles(APACHE, apachePathBaseline));
    baseline.push_back(readFiles(APACHE, apache2PathBaseline));
    baseline.push_back(readFiles(NGINX, nginxPathBaseline));
    baseline.push_back(readFiles(SSH, dovecotPathBaseline));
    baseline.push_back(readFiles(SSH, postfixPathBaseline));

    std::vector<double> outputj;
    auto bl = baseline.begin();
    for (auto cp = compare.begin(); cp != compare.end(); ++cp){
        outputj.push_back(compare_configs(*cp, *bl));
        ++bl;
    }

    for (std::vector<double>::iterator i = outputj.begin(); i != outputj.end(); ++i)
    {
        std::cout << "J = " << *i << std::endl;
    }
    return 0;



<<<<<<< HEAD
}
=======
    // for (auto& item : cs)
    //     std::cout << item << std::endl;
    //     
    run_rest_server(3000, "127.0.0.1");
    return 0;
}
>>>>>>> queen
