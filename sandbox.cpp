#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <git2.h>


struct init_libgit2 {

    init_libgit2() { git_libgit2_init(); }
    ~init_libgit2() { git_libgit2_shutdown(); }
  };

int main(int argc, const char *argv[]) {

  namespace fs = boost::filesystem;

fs::path where_i_am = fs::current_path();
auto abs_proj_dir = fs::canonical(where_i_am);

inglued::init_libgit2 init_lib{};
const char *repo_path = (abs_proj_dir.string()).c_str();
git_repository *repo = NULL;

git_repository_init(&repo, repo_path, false);
git_repository_open(&repo, repo_path);

std::vector<std::string> ignore_rules ;
std::vector<std::string> temp_ignore_rules = {"/build", "/.git", "/doc", "/node_modules"};
ignore_rules.insert(ignore_rules.begin(), temp_ignore_rules.begin(), temp_ignore_rules.end());

int ignore_file = 0;

for (std::string &ignore_rule : ignore_rules) {
       git_ignore_add_rule(repo, ignore_rule.c_str());
      }

for (fs::directory_entry &entry : fs::recursive_directory_iterator{abs_proj_dir}) {
git_ignore_path_is_ignored(&ignore_file, repo, (((entry.path()).string()).c_str()));
if (!ignore_file)
{
    std::cout<<"file complet "<<(entry.path()).string()<<std::endl;
}
else if (ignore_file)
{
    std::cout<<"griffon "<<(entry.path()).string()<<std::endl;
}
 }
}


