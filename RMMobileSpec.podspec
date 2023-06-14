#
# Be sure to run `pod lib lint RMMobileSpec.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'RMMobileSpec'
  s.version          = '1.0.3'
  s.summary          = '锐明移动端SDK'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/jgyhc/RMMobileSpec'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'jgyhc' => 'jgyhc@foxmail.com' }
  s.source           = { :git => 'https://github.com/jgyhc/RMMobileSpec.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '9.0'

#  s.source_files = 'RMMobileSpec/Classes/**/*'
  s.ios.vendored_frameworks = "**/Libs/RMMobileSDK.framework"
#  s.vendored_libraries = '**/Libs/*.a'
  
  s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  # s.resource_bundles = {
  #   'RMMobileSpec' => ['RMMobileSpec/Assets/*.png']
  # }

  # s.public_header_files = 'Pod/Classes/**/*.h'
#   s.frameworks = 'UIKit', 'Foundation', 'AVFoundation', 'MobileCoreServices', 'SystemConfiguration', 'CoreVideo', 'VideoToolbox'
#   s.libraries = 'c++', 'z', 'bz2', 'iconv.2.4.0'
  # s.dependency 'AFNetworking', '~> 2.3'
end
