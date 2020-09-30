
#include <nlohmann/json.hpp>
#include "DockerAPI.h"


using namespace std;
using nlohmann::json;

int main() {

    DockerAPI _docker("v1.40","containers");
    string prefix_query = _docker.getPrefixQ();
    HttpResponse response;
    string query = prefix_query + "lookup" + "/" + "stats"+ "?stream=false"; // "http://v1.40/containers/lookup/stats?stream=false"
    response = _docker.exec_get(query);
    json docker_stats = json::parse(response.msg);

return 0;


}
