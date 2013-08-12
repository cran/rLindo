\name{rLSwriteSolutionOfType}
\alias{rLSwriteSolutionOfType}

\title{Write the solution of a given problem to a file in a specific format.}

\description{
 R interface function for LINDO API function \code{LSwriteSolutionOfType}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSwriteSolutionOfType(model,pszFname,nFormat)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The path and name of the file to which the solution should be written.}
 \item{nFormat}{An integer specifying the file format.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSwriteSolution}}
}
