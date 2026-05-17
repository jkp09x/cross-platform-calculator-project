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
                // Job 1: Build on Ubuntu (Generic Linux)
                stage('Build - Ubuntu Linux') {
                    agent {
                        docker {
                            image 'ubuntu:22.04'
                            args '--platform linux/amd64'
                            reuseNode false
                        }
                    }
                    steps {
                        script {
                            echo "=== Building on Ubuntu Linux ==="
                            echo "Build Type: ${params.BUILD_TYPE}"
                        }
                        checkout scm
                        sh '''
                            echo "Installing dependencies..."
                            apt-get update
                            apt-get install -y build-essential cmake git
                            
                            echo "Configuring CMake..."
                            mkdir -p build
                            cd build
                            cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
                            
                            echo "Building..."
                            make
                            
                            echo "Running calculator..."
                            ./bin/calculator
                            
                            echo "Running unit tests..."
                            ctest --output-on-failure
                        '''
                    }
                }
                
                // Job 2: Build on RHEL 7 (Rocky Linux 8)
                stage('Build - RHEL 7') {
                    agent {
                        docker {
                            image 'rockylinux:8'
                            args '--platform linux/amd64'
                            reuseNode false
                        }
                    }
                    steps {
                        script {
                            echo "=== Building on RHEL 7 (Rocky Linux 8) ==="
                            echo "Build Type: ${params.BUILD_TYPE}"
                        }
                        checkout scm
                        sh '''
                            echo "Installing dependencies..."
                            yum groupinstall -y "Development Tools"
                            yum install -y cmake git
                            
                            echo "Configuring CMake..."
                            mkdir -p build
                            cd build
                            cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
                            
                            echo "Building..."
                            make
                            
                            echo "Running calculator..."
                            ./bin/calculator
                            
                            echo "Running unit tests..."
                            ctest --output-on-failure
                        '''
                    }
                }
                
                // Job 3: Build on RHEL 9 (Rocky Linux 9)
                stage('Build - RHEL 9') {
                    agent {
                        docker {
                            image 'rockylinux:9'
                            args '--platform linux/amd64'
                            reuseNode false
                        }
                    }
                    steps {
                        script {
                            echo "=== Building on RHEL 9 (Rocky Linux 9) ==="
                            echo "Build Type: ${params.BUILD_TYPE}"
                        }
                        checkout scm
                        sh '''
                            echo "Installing dependencies..."
                            dnf groupinstall -y "Development Tools"
                            dnf install -y cmake git
                            
                            echo "Configuring CMake..."
                            mkdir -p build
                            cd build
                            cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
                            
                            echo "Building..."
                            make
                            
                            echo "Running calculator..."
                            ./bin/calculator
                            
                            echo "Running unit tests..."
                            ctest --output-on-failure
                        '''
                    }
                }
                
                // // Job 4: Build on Windows (using Wine in Docker)
                // stage('Build - Windows') {
                //     agent {
                //         docker {
                //             image 'mcr.microsoft.com/windows/servercore:ltsc2022'
                //             reuseNode false
                //         }
                //     }
                //     steps {
                //         script {
                //             echo "=== Building on Windows ==="
                //             echo "Build Type: ${params.BUILD_TYPE}"
                //         }
                //         checkout scm
                //         powershell '''
                //             Write-Host "Installing dependencies..."
                //             # Note: Windows container already has build tools
                            
                //             Write-Host "Configuring CMake..."
                //             New-Item -ItemType Directory -Path build -Force | Out-Null
                //             cd build
                //             cmake -DCMAKE_BUILD_TYPE=$env:BUILD_TYPE ..
                            
                //             Write-Host "Building..."
                //             cmake --build . --config $env:BUILD_TYPE
                            
                //             Write-Host "Running calculator..."
                //             & ".\\bin\\$env:BUILD_TYPE\\calculator.exe"
                            
                //             Write-Host "Running unit tests..."
                //             ctest --output-on-failure
                //         '''
                //     }
                // }
                
                // Job 5: Build on macOS (Alpine Linux as close alternative)
                stage('Build - macOS Alternative') {
                    agent {
                        docker {
                            image 'alpine:latest'
                            reuseNode false
                        }
                    }
                    steps {
                        script {
                            echo "=== Building on Alpine Linux (macOS alternative) ==="
                            echo "Build Type: ${params.BUILD_TYPE}"
                        }
                        checkout scm
                        sh '''
                            echo "Installing dependencies..."
                            apk add --no-cache build-base cmake git
                            
                            echo "Configuring CMake..."
                            mkdir -p build
                            cd build
                            cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
                            
                            echo "Building..."
                            make
                            
                            echo "Running calculator..."
                            ./bin/calculator
                            
                            echo "Running unit tests..."
                            ctest --output-on-failure
                        '''
                    }
                }
            }
        }
    }
    
    post {
        always {
            script {
                echo "========================================"
                echo "Pipeline finished"
                echo "========================================"
            }
        }
        success {
            script {
                echo "✓ All platforms built successfully!"
            }
        }
        failure {
            script {
                echo "✗ Build failed on one or more platforms"
            }
        }
    }
}