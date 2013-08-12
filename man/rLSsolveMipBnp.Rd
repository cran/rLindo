\name{rLSsolveMipBnp}
\alias{rLSsolveMipBnp}

\title{Solve the MIP model with the branch-and-price method.}

\description{
 R interface function for LINDO API function \code{LSsolveMipBnp}. For more information,
 please refer to LINDO API User Manual.
}

\details{
This routine is appropriate for problems with good block structures.
}


\usage{
rLSsolveMipBnp(model,nBlock,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nBlock}{Number of block in the problem.}
 \item{pszFname}{An input file specifying the block structure (optional).}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnStatus}{The status of the optimization.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
