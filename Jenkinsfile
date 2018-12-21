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
                sh 'git rev-parse HEAD'
                sh "echo ${GIT_COMMIT}"
            }
        }
        stage('checkout') {
            steps {
                checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [], submoduleCfg: [], userRemoteConfigs: [[url: 'git@github.com:brave/brave-browser.git']]])
                sh """
                    if [ ! -d brave-browser-temp ]; then
                        git clone https://github.com/brave/brave-browser.git
                    else
                        git -C brave-browser-temp checkout master
                        git -C brave-browser-temp clean -fxd
                    fi
                """
            }
        }
        stage('push') {
            steps {
                sh "cat brave-browser/package.json"
            }
        }        
    }
}
