# Maintainer: pavbaranov <pavbaranov at gmail dot com>
# Maintainer: Damian N. <nycko123 at gmail>

pkgname=tweeeditor-git
_realname=TweeEditor
pkgver=1
pkgrel=1
pkgdesc="Simple text editor"
arch=('x86_64')
url="https://github.com/TweeChalice/TweeEditor"
license=('MPL')
depends=(qt5-base)
makedepends=(qt5-tools)
source=("git+https://github.com/nycko123/TweeEditor.git")
sha256sums=('SKIP')

pkgver() {
  cd "${_realname}"
  printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
    cd "${_realname}"
	cmake -DCMAKE_INSTALL_PREFIX=/usr \
		-DCMAKE_BUILD_TYPE=Release
    make
}

package() {
    install -Dm755 "$srcdir/${_realname}/TweeEdit" "$pkgdir/usr/bin/tweeeditor"
}
