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
        stage('branch') {
            steps {
                sh "echo ${GIT_COMMIT}"
                sh "echo ${GIT_BRANCH}"
                sh "rm -rf brave-browser/"
            }
        }
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
                ls -la
                ls -la brave-browser/
                git config -f brave-browser/.git/config user.name brave-builds
                git config -f brave-browser/.git/config user.email devops@brave.com

                git config -f brave-browser/.git/config --list

                git -C brave-browser status

                sed -i \'s/master/${GIT_BRANCH}/g\' brave-browser/package.json
                cat brave-browser/package.json

                git -C brave-browser status
                """
            }
        }
    }
}
