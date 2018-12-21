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
                checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [], submoduleCfg: [], userRemoteConfigs: [[credentialsId: 'brave-builds-github-token-for-pr-builder', url: 'git@github.com:brave/brave-browser.git']]])
            }
        }
        stage('push') {
            steps {
                sh "cat brave-browser/package.json"
            }
        }        
    }
}
