import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "../../../libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: "../../.."

    ofApp {
        name: { return FileInfo.baseName(sourceDirectory) }

        files: [
            'src/actions.h',
            'src/application.cpp',
            'src/application.h',
            'src/camera.cpp',
            'src/camera.h',
            'src/catmull_rom.cpp',
            'src/catmull_rom.h',
            'src/composedShape.cpp',
            'src/composedShape.h',
            'src/cursor.h',
            'src/histogram.cpp',
            'src/histogram.h',
            'src/image.h',
            'src/main.cpp',
            'src/model3D.cpp',
            'src/model3D.h',
            'src/ofApp.cpp',
            'src/ofApp.h',
            'src/parametric.cpp',
            'src/parametric.h',
            'src/primitives/circle.cpp',
            'src/primitives/circle.h',
            'src/primitives/line.cpp',
            'src/primitives/line.h',
            'src/primitives/point.cpp',
            'src/primitives/point.h',
            'src/primitives/primitive.cpp',
            'src/primitives/primitive.h',
            'src/primitives/rectangle.cpp',
            'src/primitives/rectangle.h',
            'src/primitives/square.cpp',
            'src/primitives/square.h',
            'src/primitives/triangle.cpp',
            'src/primitives/triangle.h',
            'src/primtives3D/cone.cpp',
            'src/primtives3D/cone.h',
            'src/primtives3D/cube.cpp',
            'src/primtives3D/cube.h',
            'src/primtives3D/cylinder.cpp',
            'src/primtives3D/cylinder.h',
            'src/primtives3D/primitive3D.cpp',
            'src/primtives3D/primitive3D.h',
            'src/primtives3D/sphere.cpp',
            'src/primtives3D/sphere.h',
            'src/raytracer.cpp',
            'src/raytracer.h',
            'src/renderer.cpp',
            'src/renderer.h',
            'src/sceneObject.cpp',
            'src/sceneObject.h',
            'src/sceneObject3D.cpp',
            'src/sceneObject3D.h',
            'src/star.cpp',
            'src/star.h',
        ]

        of.addons: [
            'ofxAssimpModelLoader',
            'ofxDatGui',
            'ofxHistogram',
            'ofxOpenCv',
            'ofxShaderSelect',
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
                                // and can be checked with #ifdef or #if in the code
        of.frameworks: []       // osx only, additional frameworks to link with the project
        of.staticLibraries: []  // static libraries
        of.dynamicLibraries: [] // dynamic libraries

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    property bool makeOF: true  // use makfiles to compile the OF library
                                // will compile OF only once for all your projects
                                // otherwise compiled per project with qbs
    

    property bool precompileOfMain: false  // precompile ofMain.h
                                           // faster to recompile when including ofMain.h 
                                           // but might use a lot of space per project

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
