pipeline {
    agent none
    
    parameters {
        choice(
            name: 'BUILD_TYPE',
            choices: ['Release', 'Debug'],
            description: 'Build type: Release or Debug'
        )
    }
    
    stages {
        stage('Build on Multiple Platforms') {
            parallel {
                // Job 1: Build on Linux (Generic)
                stage('Build - Ubuntu Linux') {
                    agent {
                        label 'linux'  // Jenkins agent with 'linux' label
                    }
                    steps {
                        script {
                            echo "Building on Ubuntu Linux (Release: ${params.BUILD_TYPE})"
                        }
                        checkout scm
                        sh '''
                            mkdir -p build
                            cd build
                            cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
                            make
                            ./bin/calculator
                            ctest --output-on-failure
                        '''
                    }
                }
                
                // Job 2: Build on RHEL 7
                stage('Build - RHEL 7') {
                    agent {
                        dockerContainer {
                            image 'rockylinux:8'
                            label 'linux'
                            args '--rm'
                        }
                    }
                    steps {
                        script {
                            echo "Building on RHEL 7 (Rocky Linux 8)"
                        }
                        checkout scm
                        sh '''
                            yum groupinstall -y "Development Tools"
                            yum install -y cmake
                            mkdir -p build
                            cd build
                            cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
                            make
                            ./bin/calculator
                            ctest --output-on-failure
                        '''
                    }
                }
                
                // Job 3: Build on RHEL 9
                stage('Build - RHEL 9') {
                    agent {
                        dockerContainer {
                            image 'rockylinux:9'
                            label 'linux'
                            args '--rm'
                        }
                    }
                    steps {
                        script {
                            echo "Building on RHEL 9"
                        }
                        checkout scm
                        sh '''
                            dnf groupinstall -y "Development Tools"
                            dnf install -y cmake
                            mkdir -p build
                            cd build
                            cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
                            make
                            ./bin/calculator
                            ctest --output-on-failure
                        '''
                    }
                }
                
                // Job 4: Build on Windows
                stage('Build - Windows') {
                    agent {
                        label 'windows'  // Jenkins agent with 'windows' label
                    }
                    steps {
                        script {
                            echo "Building on Windows"
                        }
                        checkout scm
                        bat '''
                            mkdir build
                            cd build
                            cmake -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ..
                            cmake --build . --config %BUILD_TYPE%
                            bin\\%BUILD_TYPE%\\calculator.exe
                            ctest --output-on-failure
                        '''
                    }
                }
                
                // Job 5: Build on macOS
                stage('Build - macOS') {
                    agent {
                        label 'macos'  // Jenkins agent with 'macos' label
                    }
                    steps {
                        script {
                            echo "Building on macOS"
                        }
                        checkout scm
                        sh '''
                            brew install cmake
                            mkdir -p build
                            cd build
                            cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
                            make
                            ./bin/calculator
                            ctest --output-on-failure
                        '''
                    }
                }
            }
        }
    }
    
    post {
        always {
            echo "Pipeline finished"
        }
        success {
            echo "✓ All platforms built successfully"
        }
        failure {
            echo "✗ Build failed on one or more platforms"
        }
    }
}