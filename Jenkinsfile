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
                sh "echo ${GIT_BRANCH_LOCAL}"
                sh "echo ${GIT_LOCAL_BRANCH}"
            }
        }
        stage('checkout') {
            steps {
                checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [], submoduleCfg: [], userRemoteConfigs: [[url: 'https://github.com/brave/brave-browser.git']]])
            }
        }
        stage('push') {
            steps {
                sh "sed \"s/master/${GIT_BRANCH}/g\" brave-browser/package.json"
            }
        }        
    }
}
