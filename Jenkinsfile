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
                sh "git clone git@github.com:brave/brave-browser.git"
                sh "cat brave-browser/package.json"
            }
        }
    }
}
