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
                script {
                    try {
                        checkout([$class: 'GitSCM', branches: [[name: "*/${GIT_BRANCH}"]], userRemoteConfigs: [[url: 'https://github.com/brave/brave-browser.git']]])
                    }
                    catch (ex) {
                        checkout([$class: 'GitSCM', branches: [[name: "*/master"]], userRemoteConfigs: [[url: 'https://github.com/brave/brave-browser.git']]])
                        // sh "git -C brave-browser checkout ${GIT_BRANCH}"
                    }
                }
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
