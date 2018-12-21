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
            }
        }
        stage('checkout') {
            steps {
                script {
                    try {
                        checkout([$class: 'GitSCM', branches: [[name: "*/${GIT_BRANCH}"]], doGenerateSubmoduleConfigurations: false, extensions: [], submoduleCfg: [], userRemoteConfigs: [[url: 'https://github.com/brave/brave-browser.git']]])
                    }
                    catch (ex) {
                        checkout([$class: 'GitSCM', branches: [[name: "*/master"]], doGenerateSubmoduleConfigurations: false, extensions: [], submoduleCfg: [], userRemoteConfigs: [[url: 'https://github.com/brave/brave-browser.git']]])
                        sh "git -C brave-browser checkout ${GIT_BRANCH}"
                    }
                }
            }
        }
        stage('push') {
            steps {
                sh """
                git config -f brave-browser/.git/config user.name brave-builds
                git config -f brave-browser/.git/config user.email devops@brave.com
                
                sed -i \"s/master/${GIT_BRANCH}/g\" brave-browser/package.json
                cat brave-browser/package.json

                git -C brave-browser status
                """
            }
        }        
    }
}
