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
                        git -C brave-browser fetch origin ${GIT_BRANCH}
                        git -C brave-browser reset --hard origin/${GIT_BRANCH}
                    fi
                """
            }
        }
        stage('config') {
            steps {
                sh """
                    git config -f brave-browser/.git/config user.name brave-builds
                    git config -f brave-browser/.git/config user.email devops@brave.com
                """
            }
        }        
        stage('pin') {
            steps {
                sh """
                    jq "del(.config.projects[\\"brave-core\\"].branch) | .config.projects[\\"brave-core\\"].commit=\\"${GIT_COMMIT}\\"" brave-browser/package.json > brave-browser/package.json.new
                    mv brave-browser/package.json.new brave-browser/package.json
                """
            }
        }
        stage('push') {
            steps {
                withCredentials([usernameColonPassword(credentialsId: 'brave-builds-github-token-for-pr-builder', variable: 'GITHUB_CREDENTIALS')]) {
                    sh "git -C brave-browser commit -a -m 'pin brave-core to ${GIT_COMMIT} from ${GIT_BRANCH}' || exit 0"
                    sh "git -C brave-browser push https://${GITHUB_CREDENTIALS}@github.com/brave/brave-browser"
                }
            }
        }
        stage('build') {
            steps {
                script {
                    def r = build job: "brave-browser-build-pr-mac/${GIT_BRANCH}", propagate: false, quietPeriod: 30
                    currentBuild.result = r.result
                }
            }
        }        
    }
}
