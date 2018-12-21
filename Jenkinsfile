pipeline {
    options {
        // disable concurrent build per branch
        disableConcurrentBuilds()
        // add timestamps to console log
        timestamps()
    }
    agent {
        node {
            // label of node on which to build
            label 'darwin-ci'
        }
    }
    // environment {
    // }
    stages {
        stage('checkout') {
            steps {
                sh """
                    if [ ! -d brave-browser ]; then
                        git clone https://github.com/brave/brave-browser.git
                    else
                        git -C brave-browser checkout -b ${GIT_BRANCH} || git -C brave-browser checkout ${GIT_BRANCH}
                        git -C brave-browser clean -fxd
                    fi
                """
            }
        }
        stage('push') {
            steps {
                sh """
                    git config -f brave-browser/.git/config user.name brave-builds
                    git config -f brave-browser/.git/config user.email devops@brave.com

                    jq 'del(.config.projects[\"brave-core\"].branch) | .config.projects[\"brave-core\"].commit=\"${GIT_COMMIT}}\"'' brave-browser/package.json > brave-browser/package.json.new
                    mv brave-browser/package.json.new brave-browser/package.json

                    git -C brave-browser commit -a -m "pin brave-core commit to ${GIT_BRANCH}"
                    git -C brave-browser show
                    git -C brave-browser status
                """
            }
        }
    }
}
